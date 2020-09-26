/* Copyright © 2020 Evgeny Zaytsev <zx_90@mail.ru>
 * 
 * Distributed under the terms of the GNU LGPL v3 license. See accompanying
 * file LICENSE or copy at https://www.gnu.org/licenses/lgpl-3.0.html
*/

#include <stdbool.h>

#include "core/token.h"

bool kar_parser_split_by_lines(KarToken* token)
{
	if (token->children_count < 1 || token->children[0]->type != KAR_TOKEN_INDENT)
	{
		return false;
	}
	size_t cursor = 0;
	while (cursor != token->children_count)
	{
		size_t j;
		for (j = cursor + 1; j < token->children_count; ++j) {
			if (token->children[j]->type == KAR_TOKEN_INDENT) {
				break;
			}
		}
		size_t k;
		for (k = cursor + 1; k < j; ++k) {
			KarToken* child = kar_token_tear_child(token, cursor + 1);
			kar_token_add_child(token->children[cursor], child);
		}
		cursor++;
	}
	return true;
}