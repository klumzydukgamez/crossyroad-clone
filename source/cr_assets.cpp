/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_assets.h"

static const GLchar emb_test_vert[] = {
#embed "cr_test.vert" suffix(, 0)
};
static const GLchar emb_test_frag[] = {
#embed "cr_test.frag" suffix(, 0)
};

namespace cr::assets {

const GLchar* const test_vert = emb_test_vert;
const GLchar* const test_frag = emb_test_frag;

} /* namespace cr::assets */
