/*
  RequestHandler.h

  Copyright (c) 2017 Ghosty Guo. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  This version is originally written by Ivan Grokhotkov for ESP8266 
  and modified by Ghosty Guo for ESP32 at 8 July 2017.
  
*/

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

class RequestHandler {
public:
    virtual ~RequestHandler() { }
    virtual bool canHandle(HTTPMethod method, String uri) { return false; }
    virtual bool canUpload(String uri) { return false; }  //currently not supported 
    virtual bool handle(ESP32WebServer& server, HTTPMethod requestMethod, String requestUri) { return false; }
    virtual void upload(ESP32WebServer& server, String requestUri, HTTPUpload& upload) {}  //currently not supported 

    RequestHandler* next() { return _next; }
    void next(RequestHandler* r) { _next = r; }

private:
    RequestHandler* _next = nullptr;
};

#endif //REQUESTHANDLER_H

