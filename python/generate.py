#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import xml.sax


class ProtoHandler( xml.sax.ContentHandler ):
    
   def __init__(self, parser):
      self.CurrentData = ""
      self.type = ""
      self.format = ""
      self.year = ""
      self.rating = ""
      self.stars = ""
      self.description = ""
      self.stack = []
      self.parser = parser
 
   
   def startElement(self, tag, attributes):
      self.CurrentData = tag
      self.stack.append(tag)

      try:
         if tag == "entry":
            if (self.stack[-2] == "interface"):
               print ("*****interface*****")
               pname = attributes["name"]
               ptype = attributes["type"]
               pdesc = attributes["desc"]
               print ("name:"+ str(pname) + ", type:"+ str(ptype) + ", pdesc:" + str(pdesc)) 
            elif (self.stack[-2] == "macrogroup"):
               pname = attributes["name"]
               pvalue = attributes["value"]
      except Exception as err:
          print("\033[0;31m%s\033[0m" % ("Error line: " + str(self.parser.getLineNumber()) +", Require key or key is invalid, " + str(err)))


   def endElement(self, tag):
       self.stack.pop();

if ( __name__ == "__main__"):
   

   parser = xml.sax.make_parser()

   parser.setFeature(xml.sax.handler.feature_namespaces, 0)
 

   Handler = ProtoHandler(parser)
   parser.setContentHandler( Handler )
   
   parser.parse("protoconfig.xml")
