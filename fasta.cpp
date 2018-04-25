#include <iostream>
#include <vector>
#include <string>
#include "fasta.hpp"

int main()
{
    Fasta a;
    std::cout << "constructor\t" << (a.name == "") << (a.seq == "") << std::endl;
    
    std::string name{"name"};
    std::string s{"ATAATGCATT"};
    Fasta b(name, s);
    std::cout << "constructor\t" << (b.name == name) << (b.seq == s) << std::endl;

    Fasta c(name, s, 2);
    std::cout << "constructor with chunk_size\t" << (c.name == name) << (c.seq == s) << (c.chunk_size == 2) << std::endl;

    Fasta d;
    d = b;
    std::cout << "copy constructor\t" << (d.name == name) << (d.seq == s) << std::endl;
    
    Fasta e(std::move(b));
    std::cout << "move constructor\t" << (e.name == name) << (e.seq == s) << (b.name.size() == 0) << (b.seq.size() == 0) << std::endl;
    
    Fasta f;
    f = std::move(c);
    std::cout << "move assignment\t" << (f.name == name) << (f.seq == s) << (c.name.size() == 0) << (c.seq.size() == 0) << std::endl;
    
    std::string str{">chr1\nATTCATTGAATC\nTATCAT"};
    Fasta g = Fasta::parse(str);
    std::cout << "parse\t" << (g.name == "chr1") << (g.seq == "ATTCATTGAATCTATCAT") << std::endl;
    
    Fasta h;
    Fasta::getobj(std::cin, h);
    
    /*
    std::vector<std::string> b{{"ATAATGCA"}, {"TT"}};
    std::string s{"ATAATGCATT"};
    std::cout << (b == s) << std::endl;*/
}
