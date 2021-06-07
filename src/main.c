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

#include "os.h"
#include "string.h"

#include "btchip_context.h"

#define RUN_APPLICATION 1

void init_coin_config(btchip_altcoin_config_t *coin_config) {
    os_memset(coin_config, 0, sizeof(btchip_altcoin_config_t));
    coin_config->bip44_coin_type = BIP44_COIN_TYPE;
    coin_config->bip44_coin_type2 = BIP44_COIN_TYPE_2;
    coin_config->p2pkh_version = COIN_P2PKH_VERSION;
    coin_config->p2sh_version = COIN_P2SH_VERSION;
    coin_config->family = COIN_FAMILY;
    strcpy(coin_config->coinid, COIN_COINID);
    strcpy(coin_config->name, COIN_COINID_NAME);
    strcpy(coin_config->name_short, COIN_COINID_SHORT);
    strcpy(coin_config->native_segwit_prefix_val, COIN_NATIVE_SEGWIT_PREFIX);
    coin_config->native_segwit_prefix = coin_config->native_segwit_prefix_val;
    coin_config->flags = COIN_FLAGS;
    coin_config->kind = COIN_KIND;
}

__attribute__((section(".boot"))) int main(int arg0) {
    BEGIN_TRY {
        TRY {
            unsigned int libcall_params[5];
            btchip_altcoin_config_t coin_config;
            init_coin_config(&coin_config);
            check_api_level(CX_COMPAT_APILEVEL);

            // delegate to bitcoin app/lib
            libcall_params[0] = "Bitcoin";
            libcall_params[1] = 0x100;
            libcall_params[2] = RUN_APPLICATION;
            libcall_params[3] = &coin_config;
            libcall_params[4] = 0;
            if (arg0) {
                // call as a library
                libcall_params[2] = ((unsigned int *)arg0)[1];
                libcall_params[4] = ((unsigned int *)arg0)[3]; // library arguments
                os_lib_call(&libcall_params);
                ((unsigned int *)arg0)[0] = libcall_params[1];
                os_lib_end();
            } else {
                // launch coin application
                os_lib_call(&libcall_params);
            }
        }
        FINALLY {}
    }
    END_TRY;

    return 0;
}
