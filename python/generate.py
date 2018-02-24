#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import xml.sax
import sys

class ProtoHandler( xml.sax.ContentHandler ):
    
   def __init__(self, parser):
      self.CurrentData = ""
      self.type = ""
      self.format = ""
      self.year = ""
      self.rating = ""
      self.stars = ""
      self.description = ""
      self.stack = [] #tag stack
      self.idst = [] #interface id stack
      self.parser = parser
      self.interfaces = {}
      self.macro = {}
  
   #==========HANDLER events===========#
   def startElement(self, tag, attributes):
      self.CurrentData = tag
      self.stack.append(tag)

      try:
         if tag == "entry":
            if (self.stack[-2] == "interface"):
               #print ("*****interface*****")
               pname = attributes["name"]
               ptype = attributes["type"]
               pdesc = attributes["desc"]
               #print ("name:"+ str(pname) + ", type:"+ str(ptype) + ", pdesc:" + str(pdesc)) 
               self.interfaces[self.idst[-1]][pname] = {};
               self.interfaces[self.idst[-1]][pname]["type"] = ptype; 
               self.interfaces[self.idst[-1]][pname]["desc"] = pdesc;
            elif (self.stack[-2] == "macrogroup"):
               pname = attributes["name"]
               pvalue = attributes["value"]
               self.macro[pname] = pvalue
         elif (tag == "interface"):
            self.idst.append(attributes["id"])
            self.interfaces[attributes["id"]] = {}
      except Exception as err:
          print("\033[0;31m%s\033[0m" % ("Error line: " + str(self.parser.getLineNumber()) +", Require key or key is invalid, " + str(err)))
          try:
             sys.exit(-1)
          finally:
             print("Error Exit with error code (-1)")

   def endElement(self, tag):
       self.stack.pop();

   
   #========DEBUGING Helpers===========#
   def printDictionary(self, dictionary, prefix):       
       for i in dictionary:
         #This will never be true but just implement it using recursive in case
         if (type(dictionary[i]) == type({})):
            print(prefix + "name:"+i)
            self.printDictionary(dictionary[i], prefix+"   ")
         else:
            print (prefix+i+":"+str(dictionary[i]))

   def printInterface(self):
       for i in self.interfaces:
          print(i+":")
          self.printDictionary(self.interfaces[i], "   ")     



if ( __name__ == "__main__"):
   

   parser = xml.sax.make_parser()

   parser.setFeature(xml.sax.handler.feature_namespaces, 0)
 

   Handler = ProtoHandler(parser)
   parser.setContentHandler( Handler )
   
   parser.parse("protoconfig.xml")

   Handler.printInterface()
