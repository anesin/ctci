// Q-17-10
//   Since XML is very verbose, you are given a way of encoding it
//   where each tag gets mapped to a pre-defined integer value.
//   The language/grammar is as follows:
//     Element   --> Tag Attributes END Children END
//     Attribute --> Tag Value
//     END       --> 0
//     Tag       --> some predefined mapping to int
//     Value     --> string value END
//   For example, the following XML might be converted into the compressed
//   string below (assuming a mapping of family -> 1, person -> 2,
//   firstName -> 3, lastName -> 4, state -> 5).
//     <family lastName="McDowell" state="CA">
//       <person firstName="Gayle">Some Message</person>
//     </family>
//   Becomes:
//     1 4 McDowell 5 CA 0 2 3 Gayle 0 Some Message 0 0.
//   Write code to print the encoded version of an XML element
//   (passed in Element and Attribute objects).
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Parser
{
public:
	// Assume that there is no useless white space.
	void Parse(const string &xml) {
		size_t begin = 0;
		while (begin != string::npos) {
			size_t end = xml.find('>', ++begin);
			if (xml[begin] == '/')
				OpenElementFinish();
			else
				OpeningTag(xml.substr(begin, end - begin));

			begin = xml.find('<', ++end);
			if (begin != string::npos && end < begin)	// value
				ParseValue(xml.substr(end, begin - end));
		}
	}

private:
	void OpeningTag(const string &opening) {
		bool is_tag = true;
		string s;
		auto ParseOpening = [&]() {
			if (is_tag) {
				OpenElementStart(s);
			}
			else {
				auto pos = s.find('=');
				ParseAttribute(s.substr(0, pos), s.substr(pos + 2, s.length() - pos - 3));
			}
		};

		for (auto &c : opening) {
			if (c != ' ') {
				s += c;
			}
			else {
				ParseOpening();
				is_tag = false;
				s.clear();
			}
		}
		if (s.length() > 0)
			ParseOpening();
		OpenElementFinish();
	}

protected:
	virtual void OpenElementStart(const string &tag) = 0;
	virtual void ParseAttribute(const string &tag, const string &value) = 0;
	virtual void OpenElementFinish() = 0;
	virtual void ParseValue(const string &text) = 0;
	virtual void CloseElement() = 0;
};

class Encoder : public Parser
{
public:
	string Encode(const string &xml) {
		enc_.clear();
		Parse(xml);
		return enc_;
	}

protected:
	virtual void OpenElementStart(const string &tag) {
		InsertDelimiter();
		if (tag == "family")
			enc_ += '1';
		else if (tag == "person")
			enc_ += '2';
	}

	virtual void ParseAttribute(const string &tag, const string &value) {
		InsertDelimiter();
		if (tag == "firstName")
			enc_ += '3';
		else if (tag == "lastName")
			enc_ += '4';
		else if (tag == "state")
			enc_ += '5';
		ParseValue(value);
	}

	virtual void OpenElementFinish() {
		CloseElement();
	}

	virtual void ParseValue(const string &value) {
		InsertDelimiter();
		enc_ += value;
	}

	virtual void CloseElement() {
		InsertDelimiter();
		enc_ += "0";
	}

private:
	void InsertDelimiter() {
		if (enc_.length() > 0)
			enc_ += ' ';
	}

	string enc_;
};



int _tmain(int argc, _TCHAR* argv[])
{
	Encoder enc;
	auto test = [&](const string &xml) {
		cout << xml << endl;
		cout << "Becomes: " << enc.Encode(xml) << endl << endl;
	};

	test("<family lastName=\"McDowell\" state=\"CA\"><person firstName=\"Gayle\">Some Message</person></family>");
	test("<family lastName=\"McDowell\" state=\"CA\"><person>Some Message</person></family>");
	test("<family><person lastName=\"McDowell\" state=\"CA\">Some Message</person></family>");

	return 0;
}

