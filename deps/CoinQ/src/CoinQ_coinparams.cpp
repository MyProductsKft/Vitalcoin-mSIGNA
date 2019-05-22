///////////////////////////////////////////////////////////////////////////////
//
// CoinQ_coinparams.cpp
//
// Copyright (c) 2012-2014 Eric Lombrozo
// Copyright (c) 2011-2016 Ciphrex Corp.
//
// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.
//

#include "CoinQ_coinparams.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include <CoinCore/CoinNodeData.h>

using namespace std;

namespace CoinQ
{

NetworkSelector::NetworkSelector(const std::string& network_name)
{
    NetworkMap_Insert(getBitcoinParams    );
    NetworkMap_Insert(getVitalcoinParams  );
    NetworkMap_Insert(getTestnet3Params   );
    NetworkMap_Insert(getLitecoinParams   );
    NetworkMap_Insert(getLtcTestnet4Params);
    NetworkMap_Insert(getQuarkcoinParams  );

    if (!network_name.empty()) { select(network_name); }
}

void NetworkSelector::NetworkMap_Insert(const CoinParams& (*pGetterFunction)())
{
    if (!pGetterFunction) return;

    const CoinParams& CP = pGetterFunction();
    string Key(CP.network_name());

    transform(Key.begin(), Key.end(), Key.begin(), ::tolower);

    network_map_.insert(NetworkPair(Key, CP));
}

vector<string> NetworkSelector::getNetworkNames() const
{
    vector<string> names;
    for (const auto& item: network_map_) { names.push_back(item.second.network_name()); }
    return names;
}

const CoinParams& NetworkSelector::getCoinParams(const std::string& network_name) const
{
    if (network_name.empty())
    {
        if (selectedCP) return *selectedCP;
        throw NetworkSelectorNoNetworkSelectedException();
    }

    string lower_network_name(network_name);

    transform(lower_network_name.begin(), lower_network_name.end(), lower_network_name.begin(), ::tolower);

    const auto& it = network_map_.find(lower_network_name);
    if (it == network_map_.end()) throw NetworkSelectorNetworkNotRecognizedException(lower_network_name);

    return it->second;
}

void NetworkSelector::select(const std::string& network_name)
{
    string lower_network_name(network_name);
    transform(lower_network_name.begin(), lower_network_name.end(), lower_network_name.begin(), ::tolower);
    const auto& it = network_map_.find(lower_network_name);
    if (it == network_map_.end()) throw NetworkSelectorNetworkNotRecognizedException(lower_network_name);

    selected_ = lower_network_name;
    selectedCP = &(it->second);

    Coin::ReportForkHash(selectedCP->forkHashExists(), selectedCP->forkHash());
}


// Coins can be added here
const CoinParams bitcoinParams(
/* uint32_t              magic_bytes_                       ; */ 0xd9b4bef9ul,
/* uint32_t              protocol_version_                  ; */ 70001,
/* const char*           default_port_                      ; */ "8333",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 0,
/* uint8_t               pay_to_script_hash_version_        ; */ 5,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 5,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 4,
/* uint8_t               pay_to_witness_script_hash_version_; */ 10,
/* uint8_t               privkey_version_                   ; */ 128,
/* const char*           network_name_                      ; */ "Bitcoin",
/* const char*           url_prefix_                        ; */ "bitcoin",
/* uint64_t              currency_divisor_                  ; */ 100000000,
/* const char*           currency_symbol_                   ; */ "BTC",
/* uint64_t              currency_max_                      ; */ 21000000,
/* uint64_t              default_fee_                       ; */ 100000,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &sha256_2,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &sha256_2,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     1,
                      /* uint32_t     timestamp_            ; */     1231006505,
                      /* uint32_t     bits_                 ; */     486604799,
                      /* uint32_t     nonce_                ; */     2083236893,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ true,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Bitcoin (v0.11.1)")
);
const CoinParams& getBitcoinParams() { return bitcoinParams; }

const CoinParams vitalcoinParams(
/* uint32_t              magic_bytes_                       ; */ 0xd9b4bef9ul,
/* uint32_t              protocol_version_                  ; */ 70001,
/* const char*           default_port_                      ; */ "6703",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 35,
/* uint8_t               pay_to_script_hash_version_        ; */ 38,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 38,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 4,
/* uint8_t               pay_to_witness_script_hash_version_; */ 10,
/* uint8_t               privkey_version_                   ; */ 176,
/* const char*           network_name_                      ; */ "Vitalcoin",
/* const char*           url_prefix_                        ; */ "vitalcoin",
/* uint64_t              currency_divisor_                  ; */ 100000000,
/* const char*           currency_symbol_                   ; */ "VTC",
/* uint64_t              currency_max_                      ; */ 230000000,
/* uint64_t              default_fee_                       ; */ 100000,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &sha256_2,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &sha256_2,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     1,
                      /* uint32_t     timestamp_            ; */     1231006505,
                      /* uint32_t     bits_                 ; */     486604799,
                      /* uint32_t     nonce_                ; */     2083236893,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ true,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Vitalcoin (v0.11.1)"),
/* bool                  forkHashExists_                    ; */ true,
/* uchar_vector          forkHash_                          ; */ uchar_vector("179ac1d7e8a5c6f882acf4b86078583b6e2ef5c03d04c36691e5a04ecb8a098e")
);
const CoinParams& getVitalcoinParams() { return vitalcoinParams; }

const CoinParams testnet3Params(
/* uint32_t              magic_bytes_                       ; */ 0x0709110bul,
/* uint32_t              protocol_version_                  ; */ 70001,
/* const char*           default_port_                      ; */ "18333",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 0x6f,
/* uint8_t               pay_to_script_hash_version_        ; */ 0xc4,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 0xc4,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 6,
/* uint8_t               pay_to_witness_script_hash_version_; */ 40,
/* uint8_t               privkey_version_                   ; */ 239,
/* const char*           network_name_                      ; */ "Testnet3",
/* const char*           url_prefix_                        ; */ "testnet3",
/* uint64_t              currency_divisor_                  ; */ 100000000,
/* const char*           currency_symbol_                   ; */ "tBTC",
/* uint64_t              currency_max_                      ; */ 21000000,
/* uint64_t              default_fee_                       ; */ 0,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &sha256_2,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &sha256_2,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     1,
                      /* uint32_t     timestamp_            ; */     1296688602,
                      /* uint32_t     bits_                 ; */     486604799,
                      /* uint32_t     nonce_                ; */     414098458,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ true,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Bitcoin TestNet3 (v0.11.1)")
);
const CoinParams& getTestnet3Params() { return testnet3Params; }

const CoinParams litecoinParams(
/* uint32_t              magic_bytes_                       ; */ 0xdbb6c0fbul,
/* uint32_t              protocol_version_                  ; */ 70002,
/* const char*           default_port_                      ; */ "9333",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 48,
/* uint8_t               pay_to_script_hash_version_        ; */ 50,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 5,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 4,
/* uint8_t               pay_to_witness_script_hash_version_; */ 10,
/* uint8_t               privkey_version_                   ; */ 176,
/* const char*           network_name_                      ; */ "Litecoin",
/* const char*           url_prefix_                        ; */ "litecoin",
/* uint64_t              currency_divisor_                  ; */ 100000000,
/* const char*           currency_symbol_                   ; */ "LTC",
/* uint64_t              currency_max_                      ; */ 84000000,
/* uint64_t              default_fee_                       ; */ 100000,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &sha256_2,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &scrypt_1024_1_1_256,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     1,
                      /* uint32_t     timestamp_            ; */     1317972665,
                      /* uint32_t     bits_                 ; */     0x1e0ffff0,
                      /* uint32_t     nonce_                ; */     2084524493,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ true,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Litecoin (v0.11.1)")
);
const CoinParams& getLitecoinParams() { return litecoinParams; }

const CoinParams ltcTestnet4Params(
/* uint32_t              magic_bytes_                       ; */ 0xf1c8d2fdul,
/* uint32_t              protocol_version_                  ; */ 70002,
/* const char*           default_port_                      ; */ "19335",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 111,
/* uint8_t               pay_to_script_hash_version_        ; */ 58,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 196,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 4,
/* uint8_t               pay_to_witness_script_hash_version_; */ 10,
/* uint8_t               privkey_version_                   ; */ 239,
/* const char*           network_name_                      ; */ "LtcTestnet4",
/* const char*           url_prefix_                        ; */ "ltctestnet4",
/* uint64_t              currency_divisor_                  ; */ 100000000,
/* const char*           currency_symbol_                   ; */ "tLTC",
/* uint64_t              currency_max_                      ; */ 84000000,
/* uint64_t              default_fee_                       ; */ 100000,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &sha256_2,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &scrypt_1024_1_1_256,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     1,
                      /* uint32_t     timestamp_            ; */     1486949366,
                      /* uint32_t     bits_                 ; */     0x1e0ffff0,
                      /* uint32_t     nonce_                ; */     293345,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("97ddfbbae6be97fd6cdf3e7ca13232a3afff2353e29badfab7f73011edd4ced9")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ false,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Litecoin TestNet4 (v0.11.1)")
);
const CoinParams& getLtcTestnet4Params() { return ltcTestnet4Params; }

const CoinParams quarkcoinParams(
/* uint32_t              magic_bytes_                       ; */ 0xdd03a5feul,
/* uint32_t              protocol_version_                  ; */ 70001,
/* const char*           default_port_                      ; */ "11973",
/* uint8_t               pay_to_pubkey_hash_version_        ; */ 0x3a,
/* uint8_t               pay_to_script_hash_version_        ; */ 0x09,
/* uint8_t               old_pay_to_script_hash_version_    ; */ 0x09,
/* uint8_t               pay_to_witness_pubkey_hash_version_; */ 4,
/* uint8_t               pay_to_witness_script_hash_version_; */ 10,
/* uint8_t               privkey_version_                   ; */ 128,
/* const char*           network_name_                      ; */ "Quarkcoin",
/* const char*           url_prefix_                        ; */ "quarkcoin",
/* uint64_t              currency_divisor_                  ; */ 100000,
/* const char*           currency_symbol_                   ; */ "QRK",
/* uint64_t              currency_max_                      ; */ 0xffffffffffffffffull / 100000,
/* uint64_t              default_fee_                       ; */ 0,
/* Coin::hashfunc_t      block_header_hash_function_        ; */ &hash9,
/* Coin::hashfunc_t      block_header_pow_hash_function_    ; */ &hash9,
/* Coin::CoinBlockHeader genesis_block_                     ; */ Coin::CoinBlockHeader(
                      /* uint32_t     version_              ; */     112,
                      /* uint32_t     timestamp_            ; */     1374408079,
                      /* uint32_t     bits_                 ; */     0x1e0fffff,
                      /* uint32_t     nonce_                ; */     12058113,
                      /* uchar_vector prevBlockHash_        ; */     uchar_vector(32, 0),
                      /* uchar_vector merkleRoot_           ; */     uchar_vector("868b2fb28cb1a0b881480cc85eb207e29e6ae75cdd6d26688ed34c2d2d23c776")
                                                                 ),
/* bool                  segwit_enabled_                    ; */ false,
/* const char*           default_host_                      ; */ "localhost",
/* std::string           user_agent_                        ; */ std::string("mSIGNA Wallet for Quarkcoin (v0.11.1)")
);
const CoinParams& getQuarkcoinParams() { return quarkcoinParams; }

/*
const CoinParams bluecoinParams(
    0xaaabf5fe, // main.cpp     pchmessageStart
    71001,      // protocol.h   PROTOCOL_VERSION
    "27104",    // 
    0x1a,
    0x1c,       // base58.h     CBitcoinAddress
    "Bluecoin",
    "bluecoin",
    1000000,    // util.h       COIN
    "BLU",
    0xffffffffffffffffull / 100000, // TODO: fix this
    &hash9,     // main.h       CBlock::GetHash() - there's a time cutoff before which scrypt_1024_1_1_256 is used
    &hash9,     //              The time cutoff is X11_CUTOFF_TIME = 1403395200 defined in main.h
    Coin::CoinBlockHeader(
        1,
        1398205046,
        0x1e0fffff, // main.cpp     bnProofOfWorkLimit
        380217,
        uchar(32, 0),
        uchar_vector("9867907dca9d8dd34cb5424091f5ef374e36407ad196fb28f6cd628fdf4e6220") // main.cpp  LoadBlockIndex
    ),
    false,
    std::string("mSIGNA Wallet for Bluecoin (v0.11.1)")
); 
const CoinParams& getBluecoinParams() { return bluecoinParams; }
*/
    
}
