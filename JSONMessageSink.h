/*
    microsoft-oms-auditd-plugin

    Copyright (c) Microsoft Corporation

    All rights reserved. 

    MIT License

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ""Software""), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef AUOMS_JSON_MESSAGE_SINK_H
#define AUOMS_JSON_MESSAGE_SINK_H

#include "MessageSinkBase.h"
#include "JSONMessageSinkBase.h"
#include "OutputBase.h"

#include <memory>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

class JSONMessageSink: virtual public MessageSinkBase, virtual public JSONMessageSinkBase {
public:
    static std::shared_ptr<MessageSinkBase> Create(std::unique_ptr<OutputBase>&& output, const Config& config) {
        return std::shared_ptr<MessageSinkBase>(static_cast<MessageSinkBase *>(new JSONMessageSink(std::move(output))));
    }

    JSONMessageSink(std::unique_ptr<OutputBase>&& output): MessageSinkBase(std::move(output)) {}

    virtual void BeginMessage(const std::string& tag, uint64_t sec, uint32_t msec);
    virtual void EndMessage();
    virtual void CancelMessage();
private:
    void send_message();
};


#endif //AUOMS_JSON_MESSAGE_SINK_H
