/*
    microsoft-oms-auditd-plugin

    Copyright (c) Microsoft Corporation

    All rights reserved. 

    MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "JSONMessageSink.h"

#include "Logger.h"

void JSONMessageSink::send_message()
{
    while(check_open()) {
        if (_output->Write(_buffer.GetString(), _buffer.GetSize()) != OutputBase::OK) {
            Logger::Warn("Write failed, closing connection");
            _output->Close();
        } else {
            return;
        }
    }
}

void JSONMessageSink::BeginMessage(const std::string& tag, uint64_t sec, uint32_t msec)
{
    double time = static_cast<double>(sec);
    time += static_cast<double>(msec)/1000;
    reset();
    _writer.StartArray();
    _writer.Key(tag.c_str(), tag.size(), true);
    _writer.Double(time);
    _writer.StartObject();
}

void JSONMessageSink::EndMessage()
{
    _writer.EndObject();
    _writer.EndArray();
    _buffer.Put('\n');

    send_message();
}

void JSONMessageSink::CancelMessage()
{
    reset();
}
