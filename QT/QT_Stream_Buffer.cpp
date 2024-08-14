#include "QT_Stream_Buffer.hpp"
#include <QString>

QT_Stream_Buffer::int_type QT_Stream_Buffer::syncput(int_type c)
{
	window->Console_Log(QString(char(c)));
	return c;
}

std::streamsize QT_Stream_Buffer::xsputn(const char_type *__s, std::streamsize __n)
{
	std::string s(__s, __n);
	window->Console_Log(QString::fromStdString(s));
	return __n;
}
