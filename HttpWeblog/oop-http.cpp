#include<iostream>
#include<fstream>
using namespace std;

class analyser
{
	string username, rfc931, remotehost, date, method, request, protocol, status, bytes, referrer, user_agent;
	
public:
	
	analyser()
	{
		username = "";
		rfc931 = "";
		remotehost = "";
		date = "";
		method = "";
		request = "";
		protocol = "";
		status = "";
		bytes = "";
		referrer = "";
		user_agent = "";
	}
	
	void set_username(string un)
	{
		this->username = un;
	}
	
	void set_rfc931(string rfc)
	{
		this->rfc931 = rfc;
	}
	
	void set_remotehost(string rh)
	{
		this->remotehost = rh;
	}
	
	void set_date(string d)
	{
		this->date = d;
	}
	
	void set_method(string meth)
	{
		this->method = meth;
	}
	
	void set_request(string req)
	{
		this->request = req;
	}
	
	void set_protocol(string proto)
	{
		this->protocol = proto;
	}
	
	void set_status(string st)
	{
		this->status = st;
	}
	
	void set_bytes(string b)
	{
		this->bytes = b;
	}
	
	void set_referrer(string ref)
	{
		this->referrer = ref;
	}
	
	void set_user_agent(string ua)
	{
		this->user_agent = ua;
	}
	
	string get_username()
	{
		return this->username;
	}
	
	string get_rfc931()
	{
		return this->rfc931;
	}
	
	string get_remotehost()
	{
		return this->remotehost;
	}
	
	string get_date()
	{
		return this->date;
	}
	
	string get_method()
	{
		return this->method;
	}
	
	string get_request()
	{
		return this->request;
	}
	
	string get_protocol()
	{
		return this->protocol;
	}
	
	string get_status()
	{
		return this->status;
	}
	
	string get_bytes()
	{
		return this->bytes;
	}
	
	string get_referrer()
	{
		return this->referrer;
	}
	
	string get_user_agent()
	{
		return this->user_agent;
	}
};

int main()
{
	freopen("output.out", "w", stdout);
	ifstream input("weblog.txt");
	string line;
	int count = 1;
	while(getline(input, line))
	{
		string username="", rfc931="", remotehost="", date="", method="", request="", protocol="", status="", bytes="", referrer="", user_agent="";
		analyser a;
		int i=0;
		//remote host
		while(line[i] != ' ')
		{
			remotehost += line[i++];
		}
		a.set_remotehost(remotehost);
		i++;
		
		//rfc931
		while(line[i] != ' ')
		{
			rfc931 += line[i++];
		}
		a.set_rfc931(rfc931);
		i++;
		
		//username
		while(line[i] != ' ')
		{
			username += line[i++];
		}
		a.set_username(username);
		i++;
		
		//date
		while(line[i] != '"')
		{
			date += line[i++];
		}
		a.set_date(date);
		i++;
		
		//method
		while(line[i] != ' ')
		{
			method += line[i++];
		}
		a.set_method(method);
		i++;
		
		//request
		while(line[i] != ' ')
		{
			request += line[i++];
		}
		a.set_request(request);
		i++;
		
		//protocol
		while(line[i] != '"')
		{
			protocol += line[i++];
		}
		a.set_protocol(protocol);
		i+=2;
		
		//status
		while(line[i] != ' ')
		{
			status += line[i++];
		}
		int status_number = (status[0]-48)*100 + (status[1]-48)*10 + (status[2]-48);
		switch(status_number)
		{
			case 200: status += " OK";
			break;
			case 201: status += " Created";
			break;
			case 202: status += " Accepted";
			break;
			case 203: status += " Partial Information";
			break;
			case 204: status += " No response";
			break;
			case 400: status += " Bad request";
			break;
			case 401: status += " Unauthorised";
			break;
			case 402: status += " Payment required";
			break;
			case 403: status += " Forbidden";
			break;
			case 404: status += " Not found";
			break;
			case 500: status += " Internal error";
			break;
			case 501: status += " Not implemented";
			break;
			case 502: status += " Overloaded service";
			break;
			case 503: status += " Gateway timeout";
			break;
			case 301: status += " Page moved";
			break;
			case 302: status += " Page found";
			break;
			case 303: status += " Method";
			break;
			case 304: status += " Not modified";
			break;
			default: break;
			
		}
		a.set_status(status);
		i++;
		
		//bytes
		while(line[i] != ' ')
		{
			bytes += line[i++];
		}
		a.set_bytes(bytes);
		i++;
		
		//referrer
		while(line[i] != ' ')
		{
			referrer += line[i++];
		}
		a.set_referrer(referrer);
		i++;
		
		//user_agent
		while(i != line.size())
		{
			user_agent += line[i++];
		}
		a.set_user_agent(user_agent);
		
		cout << "\n\n\nLog No.: " << count++;
		cout << "\nRemote Host: " << a.get_remotehost();
		cout << "\nrfc931: " << a.get_rfc931();
		cout << "\nUsername: " << a.get_username();
		cout << "\nDateTime (with time zone): " << a.get_date();
		cout << "\nMethod: " << a.get_method();
		cout << "\nRequest: " << a.get_request();
		cout << "\nProtocol: " << a.get_protocol();
		cout << "\nStatus: " << a.get_status();
		cout << "\nSize: " << a.get_bytes();
		cout << "\nReferrer: " << a.get_referrer();
		cout << "\nUser Agent: " << a.get_user_agent();
		
	}
}
