#pragma once

#include <vector>

class Message {
public:
    enum MessageType {
        RESERVED = 0,
        CONNECT = 1,	    //	Client request to connect to Server
        CONNACK = 2,	    //	Connect Acknowledgment
        PUBLISH = 3,	    //	Publish message
        PUBACK = 4,	        //	Publish Acknowledgment
        PUBREC = 5,	        //	Publish Received (assured delivery part 1)
        PUBREL = 6,	        //	Publish Release (assured delivery part 2)
        PUBCOMP = 7,	    //	Publish Complete (assured delivery part 3)
        SUBSCRIBE = 8,	    //	Client Subscribe request
        SUBACK = 9,	        //	Subscribe Acknowledgment
        UNSUBSCRIBE = 10,	//	Client Unsubscribe request
        UNSUBACK = 11,	    //	Unsubscribe Acknowledgment
        PINGREQ = 12,	    //	PING Request
        PINGRESP = 13,	    //	PING Response
        DISCONNECT = 14,	//	Client is Disconnecting
        LAST = 15	        //	Reserved
    };

    enum QoS {
        AT_MOST_ONCE = 0,   // Fire and Forget
        AT_LEAST_ONCE = 1,  // Acknowledged delivery
        EXACTLY_ONCE = 2,   // Assured delivery
        LAST = 4
    }

    Message(MessageType type);
    virtual ~Message();
    void writeVarInt(unsigned int value);

    MessageType type() const;
    void setType(MessageType type);

    QoS qos() const;
    void setQoS(QoS qos);

    bool retain() const;
    void setRetain(bool retain);

    const std::vector<unsigned char> & bytes() const;


private:
    std::vector<unsigned char> myBytes; 
};

