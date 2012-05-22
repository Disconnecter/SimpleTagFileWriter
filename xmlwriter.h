/*	
*   Class for writing some file with tags 
*	it can write xml, html and same
*	Created by Zabolotnyy S.V.
*/

#ifndef xmlwriter_h
#define xmlwriter_h

#include <iostream>
#include <String.h>
#include <vector.h>
#include <stdio.h>


class xmlwriter{
public:

	xmlwriter(char* sTmp);
	~xmlwriter();
	void CreateChild(char* sTag, char* sValue);
	void Createtag(char* sTag);
	void CloseLasttag();
	void CloseAlltags();
	void AddAtributes(char* sAttrName, char* sAttrvalue);
	void AddComment(char* sComment);
    void ChangeFile(char* sTmp);
	
private:

	char* sXmlFile;
	String data;
	void WriteAttributes();
	FILE *fp;
	int iLevel;
	vector<String> sTagStack;
	vector<String> vectAttrData;
};

#endif // xmlwriter_h
