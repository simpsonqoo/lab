#include <gtest/gtest.h>
#include "fasta.hpp"
using namespace biovoltron::format;
TEST( fasta, contructor) {

// default constructor
    Fasta fa0;
    EXPECT_EQ( fa0.name, "" );
    EXPECT_EQ( fa0.seq, ""  );
// constructor 1
    Fasta fa1("chr1", "AATTCCGTAT");
    EXPECT_EQ( fa1.name, "chr1");
    EXPECT_EQ( fa1.seq, "AATTCCGTAT");
// constructor 2
    std::size_t chunk_size = 10; //2 to the power of 10 
    Fasta fa2("chr1", "AATTCCGTAT", chunk_size);
    EXPECT_EQ( fa2.name, "chr1");
    EXPECT_EQ( fa2.seq.chunk_size(), 10); // const 
    EXPECT_EQ( fa2.seq, "AATTCCGTAT");
// copy constructor
    Fasta fa3( fa1 );
    EXPECT_EQ( fa3.name, "chr1");
    EXPECT_EQ( fa3.seq, "AATTCCGTAT");
// copy assign
    fa0 = fa1;
    EXPECT_EQ( fa0.name, "chr1");
    EXPECT_EQ( fa0.seq, "AATTCCGTAT");
// move constructor
    Fasta fa4( std::move(fa1) );
    EXPECT_EQ( fa4.name, "chr1");
    EXPECT_EQ( fa4.seq, "AATTCCGTAT");
    EXPECT_EQ( fa1.name.size(), 0 ); // space must clear after move
    EXPECT_EQ( fa1.seq.size(),  0 ); // space must clear after move
// move assign
    fa3 = std::move(fa4);
    EXPECT_EQ( fa3.name, "chr1");
    EXPECT_EQ( fa3.seq, "AATTCCGTAT");
    EXPECT_EQ( fa4.name.size(), 0 ); // space must clear after move
    EXPECT_EQ( fa4.seq.size(),  0 ); // space must clear after move

}
TEST( fasta, parse ) {
    std::string raw_data = ">chr1\nATCGCGC\nCGCGA";
    Fasta fa = Fasta::parse(raw_data);
    Fasta tmp;
    while( Fasta::getobj( std::cin, tmp) ) {

    }
    std::cin >> fa;
}
TEST( fasta, dump ) {
    Fasta fa("chr1", "AATTCCGTAT");
    std::cout << fa << std::endl;
}
