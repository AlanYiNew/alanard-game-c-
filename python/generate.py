#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import xml.sax
 
class ProtoHandler( xml.sax.ContentHandler ):
   def __init__(self):
      self.CurrentData = ""
      self.type = ""
      self.format = ""
      self.year = ""
      self.rating = ""
      self.stars = ""
      self.description = ""
 
   
   def startElement(self, tag, attributes):
      self.CurrentData = tag
      if tag == "entry":
         print ("*****entry*****")
         pname = attributes["name"]
         ptype = attributes["type"]
         pdesc = attributes["desc"]
         print ("name:"+ str(pname) + ", type:"+ str(ptype) + ", pdesc:" + str(pdesc)) 
 

if ( __name__ == "__main__"):
   

   parser = xml.sax.make_parser()

   parser.setFeature(xml.sax.handler.feature_namespaces, 0)
 

   Handler = ProtoHandler()
   parser.setContentHandler( Handler )
   
   parser.parse("protoconfig.xml")
