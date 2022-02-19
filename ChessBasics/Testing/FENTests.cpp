//
// FENTests.cpp
//
// Created by Imre Mihaly on 2022.
//
// All rights reserved.
//

#include "FEN.hpp"
#include "UnitTesting.hpp"

TEST(FEN, invalidFens) {
    std::string invalidFens[] = {
        
        // truncate
        "",
        "rn",
        "rnbqkbnr",
        "rnbqkbnr/",
        "rnbqkbnr/pppppppp/8",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ",
        
        // probably these should be enabled (somewhat cropped, but easy to correct)
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w ",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - ",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 ",
       
        // too much
        "rnbqkbnrr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/ppppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/9/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",

        // invalid chars
        "anbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/xppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/X/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/XPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/XNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR x KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR ww KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w B - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq _ 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - a 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 b",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0.1 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1.1",
        "rnbqkbnr|pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq + 0 1",
        
    };
    
    
    for(std::string fen: invalidFens) {
        REQUIRE(NULL == FEN::positionFromFEN(fen));
    }
}


TEST(FEN, validFens) {
    
    
    // just a couple of random, valid fens
    std::string validFens[] = {
        "5rk1/5p1p/1p1P2p1/8/2Pp1P1q/3Br3/P5Q1/3R1RK1 b - - 0 32",
        "5k2/5p2/8/2N1n3/5pP1/4K2P/B1b5/8 w - - 0 40",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "3rr1k1/4bpp1/7p/1p1qp3/2n3N1/2P4P/1P2QPP1/R1B1R1K1 w - - 0 26",
        "4rrk1/4bp1p/pqb1pnp1/1p2B3/5P2/P1NB2Q1/1PP3PP/4RR1K w - - 0 19",
        "r2qr1k1/1bp1bppp/p1n2n2/1p1pp3/3PP3/1BP2N1P/PP3PP1/RNBQR1K1 w - - 1 11",
        "r1r2bk1/1bqn1p2/2pp1npp/pp1Pp3/2P1P3/1P1BBNNP/P4PP1/R2QR1K1 b - - 5 22",
        "7r/p1pkn3/1p1ppbp1/8/2P1BPP1/4B3/PPP5/2KR4 w - - 0 24",
        "rnbq1rk1/ppp1bpp1/4pn1p/3p4/2PP3B/2N1PN2/PP3PPP/R2QKB1R b KQ - 0 7",
        "8/p1r5/2pkp2p/R3p1pP/2P1P1P1/4KP2/P7/8 w - - 5 33",
        "r1bqk2r/pppp1ppp/2n2n2/1Bb1p3/4P3/3P1N2/PPP2PPP/RNBQ1RK1 b kq - 2 5",
        "8/6p1/2k4p/8/1KP5/1p4P1/1R5P/7r w - - 11 53",
        "1r1qk2r/p3ppbp/5np1/P7/1pN5/1n2PP2/1P1BBP1P/R3QRK1 w k - 4 17",
        "r4rk1/ppq2ppp/5b2/3R4/3p4/1P2P1PP/P4PB1/3Q1RK1 w - - 4 22",
        "r1bq1rk1/pp2bpp1/2n2n1p/3p4/3N4/2N1B1P1/PP2PPBP/R2Q1RK1 b - - 1 11",
        "8/p3k3/bppn1p2/5Pp1/1P1PP3/4N1N1/P2K4/8 w - - 1 43",
        "rnbqk2r/ppppppbp/5np1/8/2PP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4",
        "r4rk1/2p2Npp/p2q1n2/1pbpn3/P7/1BP3Q1/1P1N1PPP/R1B2RK1 b - - 0 16",
        "rnb2rk1/pp3ppp/4pn2/2b5/2N5/6P1/PP2PPBP/R1BNK2R b KQ - 0 10",
        "r1bq1rk1/pp2nppp/2nb4/1B1p2B1/8/1N3N2/PPP2PPP/R2Q1RK1 w - - 6 11",
        "rnbqr1k1/pp3ppp/2pb4/3p4/2PP4/2nB1N2/PP3PPP/R1BQR1K1 w - - 0 11",
        "8/3n3p/3k2p1/1pp1p3/7P/rP1N2P1/7K/5R2 w - - 0 39",
        "3rr1k1/p1q2p1n/1p2p2p/2p1N1P1/2P2QP1/4P3/PP3PK1/R2R4 b - - 0 24",
        "q1r3k1/1b1nbpp1/r2p1n1p/p3pP2/NpP1P3/1B1Q2N1/PPR2BPP/4R1K1 b - - 9 23",
        "6k1/7p/2pb4/1p1n1p2/3P1p2/2P2KP1/1P5P/4BN2 b - - 1 31",
        "1r6/2b2p2/4b1k1/pp4p1/2p1P1P1/P1B5/1P2K1R1/3R4 w - - 2 46",
        "2r2rk1/1b1q1ppp/n2P4/p1pp4/7b/PP4P1/1B3PBP/2RQR1K1 w - - 0 21",
        "r1b2rk1/1p3pp1/4p2p/3nq3/4B3/pPPQP1P1/P2B3P/R4RK1 b - - 1 23",
        "4r3/5pk1/4nbp1/7p/q6P/1p2B1P1/1P2QP2/3RN1K1 w - - 1 33",
        "6k1/1pr2p2/1R5p/p7/5R2/P4P1b/8/6K1 w - - 0 37",
        "r1b1r1k1/1q1n1pbp/1ppBn1p1/p1p1P3/4P3/1P1N1NPP/P1Q2PB1/R4RK1 w - a6 0 20",
        "4k2r/p1p2ppp/1np5/1bB5/p3P3/8/PPB2PPP/3rR1K1 w k - 0 20",
        "8/p3n3/2bk1p2/3p2p1/1P3PP1/2K1PB2/3N4/8 w - g6 0 42",
        "r1br2k1/6pp/2p1pb2/P1P1N3/8/P1Q5/N2q1PPP/R3R1K1 w - - 1 22",
        "4k1nr/pr1pppbp/6p1/q1p5/2P1N3/6P1/PPQ1PP1P/R1B2RK1 b k - 1 12",
        "r1bq1rk1/pp1n1ppp/3b1n2/3pp3/3P4/1PNBPN2/P4PPP/R1BQ1RK1 w - - 0 10",
        "r3r1k1/pp3p1p/3q1np1/2np4/3N3N/2P5/PP3PPP/R2Q1RK1 w - - 0 18",
        "1rb2rk1/p2p1p1p/2n1pp2/2p5/2P5/P1qBP3/1P2NPPP/2KR3R w - - 0 14",
        "2bqrbk1/2r3pp/2p1pp2/1pPnN3/pP1P3P/P5P1/1BQ1RPB1/4R1K1 w - - 0 25",
        "1rbq1rk1/4ppbp/1npp1np1/pp6/3PP3/1P3NPP/PBPNQPB1/R3R1K1 b - - 0 12",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "r7/1p2pkb1/3p2p1/1P6/p1P5/P4K2/2b2BP1/1R3B2 w - - 0 32",
        "8/3k4/2p2p2/1p3n2/3Pq1p1/P7/1P1Q2PK/4N3 b - - 3 53",
        "r1q1r1k1/p2b1pp1/5n1p/1pP5/1p1NPP2/3B3P/P1Q3P1/2B2RK1 b - - 1 20",
        "2r1qrk1/1b4pp/np1bp3/p2pNp2/3Pn3/1PN1P1P1/PB3PBP/1QRR2K1 w - - 1 17",
        "r4rk1/ppq2ppp/5n2/2p5/2P3b1/P3Pn2/1B2BPPP/R2Q1RK1 w - - 0 15",
        "r1B5/2R5/1b1p4/p2Pk3/P7/8/6K1/8 w - - 5 45",
        "rnb2rk1/pp2ppbp/2pp1np1/q7/2PP4/2N2NP1/PP2PPBP/R1BQ1RK1 w - - 2 8",
        "2rq1r2/1p3pbk/p2p1npp/4n3/P2NPBb1/2N5/1PPQB1PP/3R1R1K w - - 8 17",
        "2bRr2k/2r2p1p/p7/1p2pN1P/1P6/4K3/PP3P2/3R4 b - - 11 40",
        "8/3bk2p/2p2p2/1pP1pP2/1P2Pn1P/R1P1NK2/8/2r5 b - - 34 63",
        "8/3R1pk1/5rp1/7p/8/5BP1/6P1/6K1 w - - 6 48",
        "2r3k1/4npb1/1q1p2pp/1n2p3/pPN1P3/1b1P1NP1/1B1Q1P1P/4RBK1 b - - 9 24",
        "r2q1rk1/1b2ppbp/p1n3p1/1pp1P3/P2P4/2P5/2B1NPPP/1RBQ1RK1 b - a3 0 14",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "r1q1rnk1/p4ppp/1p1Q4/5P2/8/4B1P1/PP3R1P/3R2K1 w - - 1 24",
        "r2r2k1/1pp1bpp1/q3p1p1/4P3/p1nP4/PnNRB2P/BP2QPP1/3R2K1 b - - 7 22",
        "3b2k1/1p4pp/p3pn2/8/N1r5/3RB2P/PP3PP1/6K1 b - - 0 26",
        "2b5/3n1k2/1p1bp2p/p2p1p2/P2P1NpN/1P2P1P1/4BPP1/6K1 w - - 0 29",
        "rnbqkbnr/pppp1ppp/4p3/8/2P5/8/PP1PPPPP/RNBQKBNR w KQkq - 0 2",
        "8/8/5p1p/1kb2K1P/4PP2/5r2/2R5/8 w - - 2 49",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "r1bq1rk1/1p2bppp/p1n1pn2/8/3P4/1BN2N2/PP3PPP/R1BQR1K1 w - - 3 11",
        "r2qr1k1/1bpn1p1p/1p1p1ppb/p7/P2PP3/2PB1N2/1P1N1PPP/R2QR1K1 w - - 1 12",
        "8/4Q3/1p4pk/p6p/3K3P/1P4P1/P1q2P2/8 b - - 0 41",
        "r1bqkbnr/pp1ppp1p/2n3p1/8/3NP3/2N5/PPP2PPP/R1BQKB1R b KQkq - 1 5",
        "4rb2/1p3p2/2p3p1/1p1k3p/1P1P4/P1R2PPP/3K1B2/8 w - - 6 43",
        "2r3k1/pp1rnp1p/2n1pbp1/8/2N1B3/P3P1P1/1P3P1P/1R2BRK1 w - - 0 21",
        "rnbqkbnr/pp2pppp/3p4/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 3",
        "4rrk1/pR3p2/6p1/3pb3/7N/6P1/P5B1/5R1K w - - 0 32",
        "3r4/p3nkb1/1p2r1pp/1P1pp3/8/1B6/P4PPP/2BRR1K1 w - - 2 26",
        "rnbqk2r/pp2bppp/3ppn2/8/3NP3/2N1BP2/PPP3PP/R2QKB1R b KQkq - 0 7",
        "3r3k/6pp/8/p3p3/1b2B3/1Pq2P2/4Q1PP/3R3K b - - 0 34",
        "2r1rk2/pb3ppp/1p1R1n2/4p3/4P3/2N2P1P/PPPN2P1/2KR4 w - - 1 18",
        "rnbqk2r/1p2ppb1/p2p3p/6p1/3NP1n1/2N3B1/PPP1BPPP/R2QK2R b KQkq - 3 10",
        "rnb2rk1/pp3ppp/4p3/q2n4/1b1N4/1QN3P1/PP1BPPBP/R3K2R b KQ - 3 10",
        "rb2r1k1/5ppp/p1pq1n2/3p4/6b1/1P2PNP1/P3BP1P/R1BQ1RK1 w - - 1 16",
        "6k1/8/5P2/8/1p6/1P1R4/2r5/3K4 b - - 4 74",
        "r1bqkb1r/1ppp1ppp/p1n2n2/4p3/B3P3/5N2/PPPP1PPP/RNBQ1RK1 b kq - 3 5",
        "8/p4pk1/B2n1q2/2pP2p1/3p1b1p/PP1NrP1P/6P1/3QR1K1 b - - 8 36",
        "8/2B5/p3k3/Pp1ppp2/1P4p1/2P2bPr/2K2R1P/8 b - - 5 49",
        "r4rk1/pRB1ppbp/2n1b1p1/8/3P4/4PN2/P3BPPP/4K2R b K - 0 16",
        "rnbqk2r/1p2bppp/p2p1n2/4p3/4P3/1NN5/PPP1BPPP/R1BQK2R w KQkq - 2 8",
        "5rk1/1pp3b1/3p2pp/2PPp3/1P2P1n1/r3B3/3NR1PP/4R1K1 b - - 2 25",
        "3r1rk1/pp3pbp/n2P1np1/2p2bN1/NQ6/4B3/PP2BPPP/R2R2K1 b - - 0 17",
        "rnbqkb1r/pp3pp1/2p1pB1p/3p4/2PP4/2N2N2/PP2PPPP/R2QKB1R b KQkq - 0 6",
        "5rk1/1pnqbpp1/2r4p/p2pP3/P1pP3B/2N2P2/1PQ3PP/R4RK1 w - - 5 25",
        "2k1r2r/1pqbb1pp/p1n1p2n/2ppP3/5B2/N1PB1N2/PP1Q1PPP/R3R1K1 b - - 5 14",
        "2kr3r/ppp1bp1p/5np1/3qNb2/3P4/2N1QP2/PP4PP/R1B1R1K1 b - - 4 15",
        "8/6p1/p2Rp1k1/1p3pP1/5P2/P7/1Pr1PK2/8 b - - 2 34",
        "8/8/3b3p/5kp1/2B5/p1N2P2/2K3nP/8 w - - 4 60",
        "3r3r/p3kp1p/1pnN2p1/4p3/5P2/4P1P1/PP1R1K1P/3R4 b - - 0 24",
        "r2r2k1/ppp1bb1p/5p2/1Pn1n3/5P2/P5PB/2N1P2P/BR1R2K1 w - - 0 24",
        "r2qkb1r/1b1n1ppp/2p1n3/pPPp4/N6N/B5P1/P4P1P/R2QKB1R b KQkq - 0 14",
        "r4rk1/1p4p1/p1pnq2p/3pNp2/1P1P3P/P3P1P1/4QP2/R1R3K1 w - - 1 22",
        "8/p7/b3ppk1/2p1P3/2P3Kp/P1P5/4B2P/8 b - - 3 32",
        "r1bq1rk1/p3bpp1/1p2pn1p/8/3p3B/1B3N2/PPP2PPP/R2QR1K1 w - - 0 13",
        "rn1q1rk1/1p2ppbp/p3bnp1/2p1N3/2PP4/3BP3/P1Q1NPPP/R1B2RK1 b - - 0 12",
        "8/5pbk/4r2p/3R4/4P3/4BKPP/8/8 b - - 0 46",
        "r3k2r/pp3p1p/2p2p2/q7/PnBP4/4P1P1/6KP/2RQ3R b kq - 2 18",
        "1rr1b1k1/1q3p1p/3ppp2/p1b5/P3P3/1PNQ1P2/N1P3PP/1K1R3R b - - 1 25",
        "rnbqkb1r/pp1p1ppp/4pn2/2p3B1/3P4/4PN2/PPP2PPP/RN1QKB1R b KQkq - 0 4",
        "r1k4r/ppp2pp1/2p1b2p/4Pn2/1b2NB2/5N1P/PPP2PP1/3R1RK1 w - - 7 14",
        "r4r1k/p1p3pp/1p1p3Q/3P1p1b/PPNK4/3P3P/2P3P1/R3R3 b - - 0 21",
        "r1b1k2r/1p3ppp/p3pn2/2q1N3/8/2PB4/PP2QPPP/R3K2R b KQkq - 1 13",
        "5r2/4QB1k/p2P4/q3B3/2p3p1/8/2b2P2/5K2 b - - 3 35",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "r3k3/1b2bp1r/pp3np1/4p3/4R1P1/1N3Q1p/PPPB3P/4R2K b q - 2 25",
        "rnb1kb1r/ppqp1ppp/4pn2/8/2PN4/6P1/PP2PP1P/RNBQKB1R w KQkq - 1 6",
        "r2qkb1r/1b1n1ppp/p1p1pn2/1p6/3P4/2NBPN2/PP3PPP/R1BQ1RK1 w kq - 0 10",
        "7k/1pp3pp/2n2n2/6B1/4p3/P6N/1r3PPP/4R1K1 w - - 0 30",
        "r1bqkb1r/pp2pp1p/2np1np1/2p5/2B1P3/3P1N2/PPP2PPP/RNBQ1RK1 w kq - 0 6",
        "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2",
        "1rb2rk1/pp2q1pp/2p2p2/3n2B1/3P4/2N3P1/PP1Q1PBP/2R3K1 w - - 0 21",
        "r2q1rk1/1b3pp1/ppn1pb1p/3p4/P2P2P1/2PB1N2/1P1N1QPP/R4RK1 b - - 2 16",
    };
    
    
    for(std::string fen: validFens) {
        Position *position = FEN::positionFromFEN(fen);
        CHECK(position != NULL);
        
        if (!position) {
            break;
        }
        std::string reconstructed = FEN::FENFromPosition(position);
        
        CHECK(reconstructed == fen);
    }
}
