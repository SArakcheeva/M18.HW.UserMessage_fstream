#include "Message.h"
#include <fstream>


Message::Message() = default;


Message::Message(std::string text, std::string sender, std::string receiver)
{
	_text = text;
	_sender = sender;
	_receiver = receiver;
}


std::string Message::getText() const
{
	return _text;
}


std::string Message::getSender() const
{
	return _sender;
}


std::string Message::getReceiver() const
{
	return _receiver;
}


std::fstream& operator >> (std::fstream& is, Message& mess)
{
	is >> mess._text;
	is >> mess._sender;
	is >> mess._receiver;
	return is;
}


std::ostream& operator << (std::ostream& os, const Message& mess)
{
	os << mess._text;
	os << ' ';
	os << mess._sender;
	os << ' ';
	os << mess._receiver;

	return os;
}