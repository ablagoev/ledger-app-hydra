/*******************************************************************************
*   Ledger App - Bitcoin Wallet
*   (c) 2016-2019 Ledger
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#ifndef BTCHIP_CONTEXT_H

#define BTCHIP_CONTEXT_H

typedef enum btchip_coin_flags_e {
    FLAG_PEERCOIN_UNITS=1,
    FLAG_PEERCOIN_SUPPORT=2,
    FLAG_SEGWIT_CHANGE_SUPPORT=4
} btchip_coin_flags_t;

typedef enum btchip_coin_kind_e {
    COIN_KIND_QTUM,
} btchip_coin_kind_t;

typedef struct btchip_altcoin_config_s {
    unsigned short bip44_coin_type;
    unsigned short bip44_coin_type2;
    unsigned short p2pkh_version;
    unsigned short p2sh_version;
    unsigned char family;
    //unsigned char* iconsuffix;// will use the icon provided on the stack (maybe)
    char coinid[14]; // used coind id for message signature prefix
    char name[16]; // for ux displays
    char name_short[6]; // for unit in ux displays
    char native_segwit_prefix_val[5];
    const char* native_segwit_prefix; // null if no segwit prefix
    unsigned int forkid;
    unsigned int zcash_consensus_branch_id;
    btchip_coin_kind_t kind;
    unsigned int flags;
} btchip_altcoin_config_t;

#endif
