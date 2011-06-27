#pragma once

#ifndef FILEVALIDATOR_H
#define FILEVALIDATOR_H

#include <QString>
#include <QDir>

class FileValidator
{
public:
	FileValidator(void);
	FileValidator(QString re, QString dir);
	FileValidator(const char* re, const char *dir);

	void setRegExpStr(QString re);
	void setRegExpStr(const char *re);
	void setDir(QString dir);
	void setDir(const char *dir);

	QString findFileInDir();

	~FileValidator(void);
private:
	QString regexpStr;
	QDir currentDir;
};
#endif
