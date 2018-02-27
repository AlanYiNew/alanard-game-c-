#!/usr/bin/python
# -*- coding: UTF-8 -*-

import xml.sax
import sys
import json

def print_err(st):
    print("\033[0;31m%s\033[0m" % st)

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
        self.enum = ""
        self.cur_interface = ""
        self.parser = parser
        self.interfaces = {}
        self.inner = {}
        self.macro = {}

#==========HANDLER events===========#
    def startElement(self, tag, attributes):
        self.CurrentData = tag
        self.stack.append(tag)
        if (self.stack[0] != "proto"):            
            print_err("Root tag must be proto")
            self.exit(-1)
                

        try:
            if tag == "entry":
                if (self.stack[-2] == "interface"):
                    pname = attributes["name"]
                    ptype = attributes["type"]
                    pdesc = attributes["desc"]
                    prequired = attributes["required"]
                    self.interfaces[self.cur_interface][pname] = {};
                    self.interfaces[self.cur_interface][pname]["type"] = ptype; 
                    self.interfaces[self.cur_interface][pname]["desc"] = pdesc;
                    self.interfaces[self.cur_interface][pname]["required"] = prequired
                elif (self.stack[-2] == "macrogroup"):
                    pname = attributes["name"]
                    pvalue = attributes["value"]
                    self.macro[pname] = pvalue
                elif (self.stack[-2] == "enum" and self.stack[-3] == "interface"):
                    self.interfaces[self.cur_interface]["enum"][self.enum][attributes["name"]] = attributes["value"]
            
            elif (tag == "interface"):
                if (attributes.__contains__("id")):
                    self.cur_interface = attributes["id"]
                    self.interfaces[attributes["id"]] = {}
                
                    if (attributes["id"] not in self.macro):
                        print_err("Invalid Id in interface, Error line: " + str(self.parser.getLineNumber()))
                        self.exit(-1)
                
                elif (attributes.__contains__("name")):
                    self.cur_interface = attributes["name"]
                    self.inner[attributes["name"]] = {}
                
                else:
                    print_err("Invalid interface. Line: " + str(self.parser.getLineNumber()));
                       

            elif (tag == "enum" and self.stack[-2] == "interface"):
                if ("enum" not in self.interfaces[self.cur_interface]):
                    self.interfaces[self.cur_interface]["enum"] = {}
                self.interfaces[self.cur_interface]["enum"][attributes["name"]] = {}
                self.enum = attributes["name"]
        
        except Exception as err:
            print_err("Error line: " + str(self.parser.getLineNumber()) +", Require key or key is invalid, key = " + str(err))
            exc_type, exc_value, exc_traceback = sys.exc_info()
            print_err("Script lineno " + str(exc_traceback.tb_lineno))
       
            self.exit(-1) 

    def exit(self, val):
        try:
            sys.exit(val)
        finally:
            print_err("Error Exit with error code "+ str(val))
   
    def endElement(self, tag):
        self.stack.pop();


#========DEBUGING Helpers===========#
    def pprint(self):
        print (json.dumps(self.macro))
        print (json.dumps(self.interfaces,indent=4))

if ( __name__ == "__main__"):

    parser = xml.sax.make_parser()

    parser.setFeature(xml.sax.handler.feature_namespaces, 0)

    Handler = ProtoHandler(parser)
    parser.setContentHandler( Handler )

    parser.parse("protoconfig.xml")

    #Handler.printInterface()
    Handler.pprint()
