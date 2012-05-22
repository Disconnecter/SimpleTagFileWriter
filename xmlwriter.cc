/*	
*   Realization Class for writing some file with tags 
*	it can write xml, html and same
*	Created by Zabolotnyy S.V.
*/

#include "xmlwriter.h"
#include <stdarg.h>
FILE* flog;


xmlwriter::xmlwriter(char* sTmp)
{
	flog = fopen("ErrXml.txt","wt");
	fprintf(flog,"constructor:\n");
	flushall();

    sXmlFile = sTmp;
    fp = NULL;
    iLevel = 0;
    //fp = fopen(sXmlFile.c_str(),"wt");
	fp = fopen(sXmlFile,"wt");
	fprintf(flog,"file open %s\n",sTmp);
	flushall();
    if(fp == NULL)
    {
		fprintf(flog,"Unable to open output file\n");	
		cout<<"Unable to open output file";
		return;
  	}
	else
	{
		fprintf(fp,"<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 1.0 Transitional//EN'>");
		fprintf(fp,"\n");
        fprintf(fp,"<meta name=""Content-Type"" content=""Content-Type:text/html; charset=UTF-8"">");  
        //fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\" \?>");
		fprintf(fp,"\n");

		fprintf(fp,"<html>");
		fprintf(fp,"\n");
		fprintf(fp,"<body>");
		fprintf(fp,"\n");
	}

	fprintf(flog,"end constructor:\n");
}

void xmlwriter::ChangeFile(char* sTmp)
{
   fprintf(fp,"</body>");
   fprintf(fp,"\n");
   fprintf(fp,"</html>");
   fprintf(fp,"\n");
   fclose(fp);      


   fp = fopen(sXmlFile,"wt");
   fprintf(flog,"change file open %s\n",sTmp);
   flushall();
   if(fp == NULL)
   {
     	fprintf(flog,"Unable to open output file\n");	
		cout<<"Unable to open output file";
		return;
  	}
	else
	{
		fprintf(fp,"<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 1.0 Transitional//EN'>");
		fprintf(fp,"\n");
        fprintf(fp,"<meta name=""Content-Type"" content=""Content-Type:text/html; charset=UTF-8"">");  
        //fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\" \?>");
		fprintf(fp,"\n");

		fprintf(fp,"<html>");
		fprintf(fp,"\n");
		fprintf(fp,"<body>");
		fprintf(fp,"\n");
	}

}



void xmlwriter::WriteAttributes()
{
   //Add Attributes
   while(0 < (vectAttrData.size()/2))
   {
      fprintf(fp," %s=", vectAttrData.back().operator char const* ());		
	  vectAttrData.pop_back();
	  fprintf(flog, "vectAttrData.back(): %s\n",vectAttrData.back().operator char const* ());
	  flushall();
	  fprintf(fp,"\"%s\"", vectAttrData.back().operator char const* ());
	  vectAttrData.pop_back();
   }
}

xmlwriter::~xmlwriter()
{
	if(fp)
        {
		 	fprintf(fp,"</body>");
			fprintf(fp,"\n");
			fprintf(fp,"</html>");
			fprintf(fp,"\n");
			fclose(fp);
		}
}


void xmlwriter::Createtag(char* sTag)
{

	fprintf(fp,"\n");

	//Indent properly
	for(int iTmp =0;iTmp<iLevel;iTmp++)
	fprintf(fp,"\t");

	fprintf(fp,"<%s",sTag);

	WriteAttributes();
	
	fprintf(fp,">");

	sTagStack.insert(sTagStack.begin(),sTag);
	
	fprintf(flog,"top Tag vector: %s  %s\n",sTagStack.front().operator char const *(), sTag);
	flushall();

	iLevel++;
	fprintf(flog,"end create tag\n");
	flushall();
}


void xmlwriter::CloseLasttag()
{
	fprintf(fp,"\n");
	iLevel--;

    //Indent properly
	for(int iTmp =0;iTmp<iLevel;iTmp++)
	fprintf(fp,"\t");

	fprintf(fp,"</%s>",sTagStack.front().operator char const* ());

	fprintf(flog,"sTagStack.front: %s\n",sTagStack.front().operator char const* ());
	flushall();	
	sTagStack.erase(sTagStack.begin());//pop out the last tag
}

void xmlwriter::CloseAlltags()
{
	while(sTagStack.size() != 0)
	{
		CloseLasttag();   
    }
}

void xmlwriter::CreateChild(char* sTag,char* sValue)
{
	fprintf(fp,"\n");
	//Indent properly
	for(int iTmp =0;iTmp<iLevel;iTmp++)
		fprintf(fp,"\t");
	
	//fprintf(fp,"<%s",sTag.c_str());
	fprintf(fp,"<%s",sTag);
	
	WriteAttributes();

	fprintf(fp,">%s</%s>",sValue,sTag);
}

void xmlwriter::AddAtributes(char* sKey, char* sVal)
{
	vectAttrData.push_back(sVal);
	vectAttrData.push_back(sKey);
}


void xmlwriter::AddComment(char* sComment)
{
	fprintf(fp,"\n");
	//Indent properly
	for(int iTmp =0;iTmp<iLevel;iTmp++)
		fprintf(fp,"\t");
	fprintf(fp,"<!--%s-->",sComment);
}
