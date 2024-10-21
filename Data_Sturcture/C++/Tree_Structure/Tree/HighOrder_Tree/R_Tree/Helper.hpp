#pragma once

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include <cassert>

// Because there is not stream support, this is a quick and dirty file I/O helper.
// Users will likely replace its usage with a Stream implementation from their favorite API.
class RTFileStream
{
    FILE *m_file;

public:
    RTFileStream()
    {
        m_file = NULL;
    }

    ~RTFileStream()
    {
        Close();
    }

    bool OpenRead(const char *a_fileName)
    {
        m_file = fopen(a_fileName, "rb");
        if (!m_file)
        {
            return false;
        }
        return true;
    }

    bool OpenWrite(const char *a_fileName)
    {
        m_file = fopen(a_fileName, "wb");
        if (!m_file)
        {
            return false;
        }
        return true;
    }

    void Close()
    {
        if (m_file)
        {
            fclose(m_file);
            m_file = NULL;
        }
    }

    template <typename TYPE>
    size_t Write(const TYPE &a_value)
    {
        ASSERT(m_file);
        return fwrite((void *)&a_value, sizeof(a_value), 1, m_file);
    }

    template <typename TYPE>
    size_t WriteArray(const TYPE *a_array, int a_count)
    {
        ASSERT(m_file);
        return fwrite((void *)a_array, sizeof(TYPE) * a_count, 1, m_file);
    }

    template <typename TYPE>
    size_t Read(TYPE &a_value)
    {
        ASSERT(m_file);
        return fread((void *)&a_value, sizeof(a_value), 1, m_file);
    }

    template <typename TYPE>
    size_t ReadArray(TYPE *a_array, int a_count)
    {
        ASSERT(m_file);
        return fread((void *)a_array, sizeof(TYPE) * a_count, 1, m_file);
    }
};




struct Helper
{

    /// Load tree contents from file
    bool Load(const char *a_fileName)
    {
        RemoveAll(); // Clear existing tree

        RTFileStream stream;
        if (!stream.OpenRead(a_fileName))
        {
            return false;
        }

        bool result = Load(stream);

        stream.Close();

        return result;
    }
    /// Load tree contents from stream
    bool Load(RTFileStream &a_stream)
    {
        // Write some kind of header
        int _dataFileId = ('R' << 0) | ('T' << 8) | ('R' << 16) | ('E' << 24);
        int _dataSize = sizeof(DATATYPE);
        int _dataNumDims = NUMDIMS;
        int _dataElemSize = sizeof(ELEMTYPE);
        int _dataElemRealSize = sizeof(ELEMTYPEREAL);
        int _dataMaxNodes = TMAXNODES;
        int _dataMinNodes = TMINNODES;

        int dataFileId = 0;
        int dataSize = 0;
        int dataNumDims = 0;
        int dataElemSize = 0;
        int dataElemRealSize = 0;
        int dataMaxNodes = 0;
        int dataMinNodes = 0;

        a_stream.Read(dataFileId);
        a_stream.Read(dataSize);
        a_stream.Read(dataNumDims);
        a_stream.Read(dataElemSize);
        a_stream.Read(dataElemRealSize);
        a_stream.Read(dataMaxNodes);
        a_stream.Read(dataMinNodes);

        bool result = false;

        // Test if header was valid and compatible
        if ((dataFileId == _dataFileId) && (dataSize == _dataSize) && (dataNumDims == _dataNumDims) && (dataElemSize == _dataElemSize) && (dataElemRealSize == _dataElemRealSize) && (dataMaxNodes == _dataMaxNodes) && (dataMinNodes == _dataMinNodes))
        {
            // Recursively load tree
            result = LoadRec(m_root, a_stream);
        }

        return result;
    }

    /// Save tree contents to file
    bool Save(const char *a_fileName)
    {
        RTFileStream stream;
        if (!stream.OpenWrite(a_fileName))
        {
            return false;
        }

        bool result = Save(stream);

        stream.Close();

        return result;
    }
    /// Save tree contents to stream
    bool Save(RTFileStream &a_stream)
    {
        // Write some kind of header
        int dataFileId = ('R' << 0) | ('T' << 8) | ('R' << 16) | ('E' << 24);
        int dataSize = sizeof(DATATYPE);
        int dataNumDims = NUMDIMS;
        int dataElemSize = sizeof(ELEMTYPE);
        int dataElemRealSize = sizeof(ELEMTYPEREAL);
        int dataMaxNodes = TMAXNODES;
        int dataMinNodes = TMINNODES;

        a_stream.Write(dataFileId);
        a_stream.Write(dataSize);
        a_stream.Write(dataNumDims);
        a_stream.Write(dataElemSize);
        a_stream.Write(dataElemRealSize);
        a_stream.Write(dataMaxNodes);
        a_stream.Write(dataMinNodes);

        // Recursively save tree
        bool result = SaveRec(m_root, a_stream);

        return result;
    }

    /// Iterator is not remove safe.
    class Iterator
    {
    private:
        enum
        {
            MAX_STACK = 32
        }; //  Max stack size. Allows almost n^32 where n is number of branches in node

        struct StackElement
        {
            Node *m_node;
            int m_branchIndex;
        };

    public:
        Iterator() { Init(); }

        ~Iterator() {}

        /// Is iterator invalid
        bool IsNull() { return (m_tos <= 0); }

        /// Is iterator pointing to valid data
        bool IsNotNull() { return (m_tos > 0); }

        /// Access the current data element. Caller must be sure iterator is not NULL first.
        DATATYPE &operator*()
        {
            ASSERT(IsNotNull());
            StackElement &curTos = m_stack[m_tos - 1];
            return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
        }

        /// Access the current data element. Caller must be sure iterator is not NULL first.
        const DATATYPE &operator*() const
        {
            ASSERT(IsNotNull());
            StackElement &curTos = m_stack[m_tos - 1];
            return curTos.m_node->m_branch[curTos.m_branchIndex].m_data;
        }

        /// Find the next data element
        bool operator++() { return FindNextData(); }

        /// Get the bounds for this node
        void GetBounds(ELEMTYPE a_min[NUMDIMS], ELEMTYPE a_max[NUMDIMS])
        {
            ASSERT(IsNotNull());
            StackElement &curTos = m_stack[m_tos - 1];
            Branch &curBranch = curTos.m_node->m_branch[curTos.m_branchIndex];

            for (int index = 0; index < NUMDIMS; ++index)
            {
                a_min[index] = curBranch.m_rect.m_min[index];
                a_max[index] = curBranch.m_rect.m_max[index];
            }
        }

    private:
        /// Reset iterator
        void Init() { m_tos = 0; }

        /// Find the next data element in the tree (For internal use only)
        bool FindNextData()
        {
            for (;;)
            {
                if (m_tos <= 0)
                {
                    return false;
                }
                StackElement curTos = Pop(); // Copy stack top cause it may change as we use it

                if (curTos.m_node->IsLeaf())
                {
                    // Keep walking through data while we can
                    if (curTos.m_branchIndex + 1 < curTos.m_node->m_count)
                    {
                        // There is more data, just point to the next one
                        Push(curTos.m_node, curTos.m_branchIndex + 1);
                        return true;
                    }
                    // No more data, so it will fall back to previous level
                }
                else
                {
                    if (curTos.m_branchIndex + 1 < curTos.m_node->m_count)
                    {
                        // Push sibling on for future tree walk
                        // This is the 'fall back' node when we finish with the current level
                        Push(curTos.m_node, curTos.m_branchIndex + 1);
                    }
                    // Since cur node is not a leaf, push first of next level to get deeper into the tree
                    Node *nextLevelnode = curTos.m_node->m_branch[curTos.m_branchIndex].m_child;
                    Push(nextLevelnode, 0);

                    // If we pushed on a new leaf, exit as the data is ready at TOS
                    if (nextLevelnode->IsLeaf())
                    {
                        return true;
                    }
                }
            }
        }

        /// Push node and branch onto iteration stack (For internal use only)
        void Push(Node *a_node, int a_branchIndex)
        {
            m_stack[m_tos].m_node = a_node;
            m_stack[m_tos].m_branchIndex = a_branchIndex;
            ++m_tos;
            ASSERT(m_tos <= MAX_STACK);
        }

        /// Pop element off iteration stack (For internal use only)
        StackElement &Pop()
        {
            ASSERT(m_tos > 0);
            --m_tos;
            return m_stack[m_tos];
        }

        StackElement m_stack[MAX_STACK]; ///< Stack as we are doing iteration instead of recursion
        int m_tos;                       ///< Top Of Stack index

        friend RTree; // Allow hiding of non-public functions while allowing manipulation by logical owner
    };

    /// Get 'first' for iteration
    void GetFirst(Iterator &a_it)
    {
        a_it.Init();
        Node *first = m_root;
        while (first)
        {
            if (first->IsInternalNode() && first->m_count > 1)
            {
                a_it.Push(first, 1); // Descend sibling branch later
            }
            else if (first->IsLeaf())
            {
                if (first->m_count)
                {
                    a_it.Push(first, 0);
                }
                break;
            }
            first = first->m_branch[0].m_child;
        }
    }

    /// Get Next for iteration
    void GetNext(Iterator &a_it) { ++a_it; }

    /// Is iterator NULL, or at end?
    bool IsNull(Iterator &a_it) { return a_it.IsNull(); }

    /// Get object at iterator position
    DATATYPE &GetAt(Iterator &a_it) { return *a_it; }

    bool SaveRec(Node *a_node, RTFileStream &a_stream)
    {
        a_stream.Write(a_node->m_level);
        a_stream.Write(a_node->m_count);

        if (a_node->IsInternalNode()) // not a leaf node
        {
            for (int index = 0; index < a_node->m_count; ++index)
            {
                Branch *curBranch = &a_node->m_branch[index];

                a_stream.WriteArray(curBranch->m_rect.m_min, NUMDIMS);
                a_stream.WriteArray(curBranch->m_rect.m_max, NUMDIMS);

                SaveRec(curBranch->m_child, a_stream);
            }
        }
        else // A leaf node
        {
            for (int index = 0; index < a_node->m_count; ++index)
            {
                Branch *curBranch = &a_node->m_branch[index];

                a_stream.WriteArray(curBranch->m_rect.m_min, NUMDIMS);
                a_stream.WriteArray(curBranch->m_rect.m_max, NUMDIMS);

                a_stream.Write(curBranch->m_data);
            }
        }

        return true; // Should do more error checking on I/O operations
    }
    bool LoadRec(Node *a_node, RTFileStream &a_stream)
    {
        a_stream.Read(a_node->m_level);
        a_stream.Read(a_node->m_count);

        if (a_node->IsInternalNode()) // not a leaf node
        {
            for (int index = 0; index < a_node->m_count; ++index)
            {
                Branch *curBranch = &a_node->m_branch[index];

                a_stream.ReadArray(curBranch->m_rect.m_min, NUMDIMS);
                a_stream.ReadArray(curBranch->m_rect.m_max, NUMDIMS);

                curBranch->m_child = AllocNode();
                LoadRec(curBranch->m_child, a_stream);
            }
        }
        else // A leaf node
        {
            for (int index = 0; index < a_node->m_count; ++index)
            {
                Branch *curBranch = &a_node->m_branch[index];

                a_stream.ReadArray(curBranch->m_rect.m_min, NUMDIMS);
                a_stream.ReadArray(curBranch->m_rect.m_max, NUMDIMS);

                a_stream.Read(curBranch->m_data);
            }
        }

        return true; // Should do more error checking on I/O operations
    }
};
