#include <string>
#include <vector>
#include <iostream>

typedef int32_t INT;

class Fasta
{
  public:
    std::string name;
    std::vector<std::string> seq;
    INT chunk_size = 8;

    Fasta(): name(""), seq({""}){}

    void set_vec(std::vector<std::string>& vec, const std::string& str)
    {
	std::string tmp{""};
	INT vec_size;
	if(str.size() & (chunk_size - 1))
	    vec_size = str.size() / chunk_size + 1;
	else
	    vec_size = str.size() / chunk_size;

	vec.resize(vec_size);

	for(INT i = 0, vec_idx = 0; i != str.size(); ++i)
	{

	    //std::cout << "i:" << i << str[i];
	    //push_back
	    if((i & (chunk_size - 1)) == 0 && i)
	    {
		vec[vec_idx] = tmp;
		tmp.clear();
		++vec_idx;
	    }

	    //new char
	    tmp += str[i];

	    //last string
	    if(i == str.size() - 1)
	    {
		vec[vec_idx] = tmp;
	    }
	}
    }

    Fasta(std::string name_in, std::string seq_in)
    {
	name = name_in;
	set_vec(seq, seq_in);
    }

    //copy constructor
    Fasta(const std::string& name_in, const std::string& seq_in, const int chunk_in)
    {
	name = name_in;
	chunk_size = chunk_in;
	set_vec(seq, seq_in);
    }

    //copy assignment
    Fasta& operator=(const Fasta& k)
    {
	name = k.name;
	seq = k.seq;
	chunk_size = k.chunk_size;
	return *this;
    }

    Fasta(Fasta&& k): name(std::move(k.name)), 
		seq(std::move(k.seq)), chunk_size(std::move(k.chunk_size)){}

    Fasta& operator=(Fasta&& k)
    {
	name = std::move(k.name);
	seq = std::move(k.seq);
	chunk_size = std::move(k.chunk_size);

	return *this;
    }

    static Fasta parse(const std::string& str)
    {
	std::string str_name;
	std::string str_seq;
	bool flag = false;

	for(INT i = 0; i != str.size(); ++i)
	{
	    if(!flag)
	    {
		if(str[i] == '>')
		    continue;
		if(str[i] == '\n')
		{
		    flag = true;
		    continue;
		}
		str_name += str[i];
	    }
	    else
		if(str[i] == '\n')
		{
		    flag = true;
		    continue;
		}
		else
		    str_seq += str[i];
	}

	Fasta f(str_name, str_seq, 8);
	return f;
    }

    static Fasta parse(const std::string& str, const INT chunk)
    {	
	std::string str_name;
	std::string str_seq;
	bool flag = false;

	for(INT i = 0; i != str.size(); ++i)
	{
	    if(!flag)
	    {
		if(str[i] == '>')
		    continue;
		if(str[i] == '\n')
		{
		    flag = true;
		    continue;
		}
		str_name += str[i];
	    }
	    else
		if(str[i] == '\n')
		{
		    flag = true;
		    continue;
		}
		else
		    str_seq += str[i];
	}

	Fasta f(str_name, str_seq, chunk);
	return f;
    }
    
    static bool getobj(std::istream in, Fasta& tmp)
    {
	std::string str_tmp;
	in >> str_tmp;
	
	tmp = parse(str_tmp);	
    }
/*
    friend std::istream &operator>>(std::istream& in, Fasta& tmp)
    {
	getobj(in, tmp);
	//return in;
    }*/
};


bool operator==(const std::vector<std::string>& seq, const std::string str)
{
    bool eq = true;
    for(INT i = 0, j = 0, seq_idx = 0; i != str.size(); ++i, ++j)
    {
	if(j == seq[seq_idx].size())
	{
	    j = 0;
	    ++seq_idx; 
	}

	eq = eq && (seq[seq_idx][j] == str[i]);

	if(i == str.size() - 1)
	{
	    if(seq_idx != seq.size() - 1)
		return false;
	    if(j != seq[seq_idx].size() - 1)
		return false;
	}
    }

    return eq;
}
