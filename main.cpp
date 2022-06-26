/*
 * main.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: q
 */

#include <iostream>
#include <cstring>
#include <Mixed.h>
#include <php2cpp.h>

using namespace std;

typedef map<long, Mixed> arr_lm;
arr_ls __operators = { { 0, ":" }, { 1, "::" }, { 2, "=" }, { 3, "==" }, { 4,
		">" }, { 5, "<" }, { 6, "==" }, { 7, "!==" }, { 8, "." }, { 9, "," }, {
		10, ":" }, { 11, "+" }, { 12, ">=" }, { 13, "<=" }, { 14, "!=" }, { 15,
		"!" }, { 16, "-" }, { 17, "*" }, { 18, "/" }, { 19, "%" }, { 20, "+:" },
		{ 21, "++" }, { 22, "-:" }, { 23, "--" }, { 24, ".:" }, { 25, "[]" }, {
				26, "*:" }, { 27, "/:" }, { 28, "%:" }, { 29, "<>" },
		{ 30, "?" }, { 31, "=>" }, { 32, "->" }, { 33, ">>" }, { 34, "<<" }, {
				35, ".." }, { 36, "&&" }, { 37, "||" }, { 38, "|&" },
		{ 39, "(" }, { 40, ")" }, { 41, "{" }, { 42, "}" }, { 43, "[" }, { 44,
				"]" } };
arr_ls __operator_1st_chars;
arr_lls __operators_by_chars_count = { { 3, { } }, { 2, { } }, { 1, { } } };
arr_sll __real_operators = { { "=", { { 0, 2 }, { 1, 3 } } }, { "==", {
		{ 0, 2 }, { 1, 5 } } }, { ">", { { 0, 2 }, { 1, 4 } } }, { "<", {
		{ 0, 2 }, { 1, 4 } } }, { "!==", { { 0, 2 }, { 1, 5 } } }, { ".", { { 0,
		2 }, { 1, 3 } } }, { ",", { { 0, 2 }, { 1, 3 } } }, { "+", { { 0, 2 }, {
		1, 3 } } }, { ">=", { { 0, 2 }, { 1, 4 } } }, { "<=", { { 0, 2 },
		{ 1, 4 } } }, { "!=", { { 0, 2 }, { 1, 5 } } }, { "!", { { 0, 1 }, { 1,
		1 } } }, { "-", { { 0, 2 }, { 1, 3 } } },
		{ "*", { { 0, 2 }, { 1, 2 } } }, { "/", { { 0, 2 }, { 1, 2 } } }, { "%",
				{ { 0, 2 }, { 1, 2 } } }, { ":", { { 0, 2 }, { 1, 6 } } }, {
				"+:", { { 0, 2 }, { 1, 6 } } },
		{ "++", { { 0, 0 }, { 1, 3 } } }, { "-:", { { 0, 2 }, { 1, 3 } } }, {
				"--", { { 0, 0 }, { 1, 6 } } },
		{ ".:", { { 0, 2 }, { 1, 6 } } }, { "[]", { { 0, 0 }, { 1, 0 } } }, {
				"*:", { { 0, 2 }, { 1, 6 } } },
		{ "/:", { { 0, 2 }, { 1, 6 } } }, { "%:", { { 0, 2 }, { 1, 6 } } }, {
				"<>", { { 0, 2 }, { 1, 5 } } },
		{ "&&", { { 0, 2 }, { 1, 7 } } }, { "||", { { 0, 2 }, { 1, 9 } } }, {
				"|&", { { 0, 2 }, { 1, 8 } } } };
arr_ls __keywords = { { 0, "if" }, { 1, "else" }, { 2, "class" }, { 3, "do" }, {
		4, "while" }, { 5, "break" }, { 6, "use" }, { 7, "switch" },
		{ 8, "new" }, { 9, "continue" }, { 10, "return" }, { 11, "include" }, {
				12, "throw" }, { 13, "try" }, { 14, "catch" },
		{ 15, "finally" }, { 16, "defcat" }, { 17, "deffi" }, { 18, "else if" },
		{ 19, "new" }, { 20, "do" }, { 21, "case" }, { 22, "continue" }, { 23,
				"for" }, { 24, "times" }, { 25, "from" }, { 26, "to" }, { 27,
				"foreach" }, { 28, "as" }, { 29, "at" } };
arr_ls __modifiers = { { 0, "private" }, { 1, "public" }, { 2, "static" } };
const string PHP_EOL = "\n";
const string CPP_EOL = "\n";
Mixed __funcs, __classes, __main;

//string array_reconstruct(Mixed $arr, long $level) {
//	string $tab;
//	long $i;
//	string $k1;
//	Mixed $e1;
//	$tab = "";
//	for ($i = 0; $i < $level; $i++)
//		$tab += "\t";
//	for (auto  [$k1, $e1] : $arr.valueArray) {
//		if (((Mixed) $e1).type != "a")
//			$arr[$k1] = $tab+""\""+$k1+""\" => \"$e1\"";
//		else
//			$arr[$k1] = "$tab\"$k1\" => " + array_reconstruct($e1, $level + 1);
//	}
//
//	return "[" + PHP_EOL + implode("," + PHP_EOL, $arr.valueArray) + PHP_EOL
//			+ $tab + "]";
//}
Mixed array_merge(Mixed _arr, tokens_line _arr1) {
	for (auto [_key, _value] : _arr1) {
		_arr.push(_value);
	}
	return _arr;
}
bool is_az(string _inp) {
	long _i1;
	bool _is_matches;
	for (_i1 = 0; _i1 < strlen(_inp); _i1++) {
		_is_matches = php_preg_match("/[a-zA-Z]/", php_to_string(_inp.at(_i1)));
		if (_is_matches)
			return false;
	}
	return true;
}
Mixed get_1st_ele(Mixed _arr) {
	tokens_line1 _ele;
	if (!_arr.valueArray.empty())
		return _arr.valueArray.begin()->second;
	return Mixed();
}
tokens_line1 get_last_ele(tokens_line1_arr _arr) {
	tokens_line1 _ele;
	if (!_arr.empty())
		return _arr.rbegin()->second;
	return tokens_line1();
}
string remove_from_string(string $str, long $start, long $stop) {
	if ($start >= $stop || $stop > strlen($str))
		return $str;
	$str = substr($str, 0, $start) + " " + substr($str, $stop + 1);
	return $str;
}
long get_first_pos_or_end_of_str(string $content, string $str,
		long $start_pos) {
	long $pos_end;
	$pos_end = strpos($content, $str, $start_pos);
	if ($pos_end == -1)
		$pos_end = strlen($content);
	else
		$pos_end += strlen($str);
	return $pos_end;
}
string remove_comment_blocks(string $content) {
	long $len;
	long $i;
	long $last_pos;
	$len = strlen($content);
	$i = 0;
	while ($i < $len - 1) {
		if (to_string($content.at($i)) + to_string($content.at($i + 1))
				== "/*") {
			$last_pos = get_first_pos_or_end_of_str($content, "*/", $i);
			$content = remove_from_string($content, $i, $last_pos);
			$len = strlen($content);
		}
		$i++;
	}
	return $content;
}
string remove_inline_comments(string $content) {
	arr_ls $arr;
//	long $k;
	string $v;
	long $pos;
	$arr = explode("\n", $content);
	for (auto [$k, $v] : $arr) {
		if (($pos = strpos($v, "//")) != false)
			$arr[$k] = substr($v, 0, $pos);
	}
	return implode("\n", $arr);
}
string remove_comments(string $content) {
	$content = remove_inline_comments($content);
	$content = remove_comment_blocks($content);
	return $content;
}
string rtrim_all_lines(string $content) {
	arr_ls $arr;
//	long $k;
	string $v;
	$arr = explode("\n", $content);
	for (auto [$k, $v] : $arr) {
		$arr[$k] = rtrim($v);
	}
	return implode("\n", $arr);
}
tokens_line1_arr rtrim_all_lines_arr(tokens_line1_arr $content) {
//	long $k0;
	tokens_line1 $line;
//	long $k1;
	token $token;
	long $kx;
	for (auto [$k0, $line] : $content) {
		for (auto [$k1, $token] : ((tokens_line1) $line).$0) {
			if ($token.$1 != "spaces") {
				$kx = $k1;
				break;
			}
			$content[$k0].$0 = array_slice(((tokens_line1) $line).$0, $kx,
					sizeof(((tokens_line1) $line).$0));
		}
	}
	return $content;
}
string tokens_arr_to_str1(tokens_line $tokens_line1_arr) {
	string $return;
	token $token;
	$return = "";
	for (auto [$key_rtt, $token] : $tokens_line1_arr) {
		$return += $token.$0;
	}
	return $return;
}
tokens_line_arr explode_tokens(token $del, tokens_line $tokens_line1_arr) {
	tokens_line_arr $return;
	long $k;
	token $token;
	$return = { { 0, { } } };
	$k = 0;
	for (auto [$key_rtt, $token] : $tokens_line1_arr) {
		if ((token) $token == $del) {
			$k++;
			$return[$k] = { };
		} else {
			array_push($return[$k], $token);
		}
	}
	return $return;
}
tokens_line_arr explode_tokens(string $del, tokens_line $tokens_line1_arr) {
	tokens_line_arr $return;
	long $k;
	token $token;
	$return = { { 0, { } } };
	$k = 0;
	for (auto [$key_rtt, $token] : $tokens_line1_arr) {
		if ($token.$0 == $del) {
			$k++;
			$return[$k] = { };
		} else {
			array_push($return[$k], $token);
		}
	}
	return $return;
}
arr_ll array_search_multi(token $search, tokens_line $arr) {
	arr_ll $return;
//	long $k;
	token $v;
	$return = { };
	for (auto [$k, $v] : $arr) {
		if ($search == $v)
			array_push($return, $k);
	}
	return $return;
}

tokens_line remove_spaces_from_tokens_arr(tokens_line $tokens_line1_arr) {
	tokens_line $return;
	token $token;
	$return = { };
	for (auto [$key_rtt, $token] : $tokens_line1_arr) {
		if (($token.$1 != "") && $token.$1 != "spaces")
			array_push($return, $token);
	}
	return $return;
}
Mixed remove_spaces_from_tokens_arr(Mixed $tokens_line1_arr) {
	Mixed $return;
	for (auto [$key_rtt, $token] : $tokens_line1_arr.valueArray) {
		if (!($token[1] == "") && !($token[1] == "spaces"))
			$return.push($token);
	}
	return $return;
}
// ========================================================================================;
// ========================================================================================;
// ========================================================================================;
Mixed parse_expression(tokens_line tokens_arr);
bool is_blank_str(string $str) {
	for (long $i = 0; $i < strlen($str); $i++)
		if (to_string($str.at($i)) != " " && to_string($str.at($i)) != "\t")
			return false;
	return true;
}
string remove_blank_lines(string $content) {
	arr_ls $arr;
	string $v;
	$arr = explode("\n", $content);
	for (auto [$k, $v] : $arr) {
		if (is_blank_str($v))
			$arr.erase($k);
	}
	return implode("\n", $arr);
}
string process_first_line(string $content) {
	arr_ls $arr;
	string $first_line;
	$arr = explode("\n", $content);
	$first_line = trim($arr[0]);
	if (strpos($first_line, "#") == 0)
		array_shift($arr);
	return implode("\n", $arr);
}
void new_line(tokens_line1_arr &$arr, long &$line) {
	$line++;
	if (!isset($arr, $line))
		$arr[$line] = { { }, 0 };
}
tokens_line1_arr tokenize(string $content) {
	tokens_line1_arr $output_arr;
	long $len;
	long $line;
	long $block_lv;
	long $i;
	long $i1;
	string $extracted_str;
	bool $matches;
	string $;
	string $answer_var;
	string $list_params;
//	long $char_count;
	tokens_line $operators;
	string $operator;
	string $output_line;
	$content = process_first_line($content);
	$output_arr = { };
	$content = remove_comments($content);
	$content = remove_blank_lines($content);
	$content = string("\n") + rtrim_all_lines($content);
	$len = strlen($content);
	$line = 0;
	$block_lv = 0;
	for ($i = 0; $i < $len; $i++) {
// new_line ( $output_arr, $line );
// if (! isset ( $output_arr [$line] ))
// $output_arr [$line] = [ 0 => Mixed(),1 => 0
// ];
		if (php_to_string($content.at($i)) == "\n" && strlen($content) > $i
				&& to_string($content.at($i + 1)) == "\n") {
			$i += 1;
			continue;
		} else if (substr($content, $i, 3) == "...") {
			$i += 2;
		} else if (php_to_string($content.at($i)) == "\n"
				&& substr($content, $i - 3, 3) == "...") {
			$i += 3;
		} else if (php_to_string($content.at($i)) == ":") {
			new_line($output_arr, $line);
		} else if (php_to_string($content.at($i)) == "\n") {
			new_line($output_arr, $line);
// ignore first tabs and spaces;
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				if (php_to_string($content.at($i + $i1)) != " "
						&& php_to_string($content.at($i + $i1)) != "\t")
					break;
			}
			$extracted_str = substr($content, $i + 1, $i1 - 1);
			$extracted_str = str_ireplace("\t", "    ", $extracted_str);
			$block_lv = round(strlen($extracted_str) / 4);
			$output_arr[$line].$1 = $block_lv;
			$i += $i1 - 1;
		} else if (php_to_string($content.at($i)) == " "
				|| php_to_string($content.at($i)) == "\t") {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				if (php_to_string($content.at($i + $i1)) != " ")
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			array_push($output_arr[$line].$0, { $extracted_str, "spaces" });
		} else if (php_to_string($content.at($i)) == " "
				|| php_to_string($content.at($i)) == "\t") {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				if (php_to_string($content.at($i + $i1)) != " ")
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			array_push($output_arr[$line].$0, { $extracted_str, "spaces" });
		} else if (php_to_string($content.at($i)) == "\\"
				&& strlen($content) > $i) {
			for ($i1 = 2; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
// if (strlen ( $extracted_str ) == 1)
// throw  ( "wrong string format" );
			array_push($output_arr[$line].$0, { $extracted_str, "string" });
			$i += $i1 - 1;
		} else if (php_to_string($content.at($i)) == "$"
				&& php_to_string($content.at($i + 1)) == "?") {
			array_push($output_arr[$line].$0, { "$answer_var", "var" });
			$i += 1;
			continue;
		} else if (php_to_string($content.at($i)) == "$"
				&& php_to_string($content.at($i + 1)) == "@") {
			array_push($output_arr[$line].$0, { "$list_params", "var" });
			$i += 1;
			continue;
		} else if (php_to_string($content.at($i)) == "$"
				&& php_to_string($content.at($i + 1)) == "$") {
			for ($i1 = 2; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1)
				throw "wrong var format";
			array_push($output_arr[$line].$0, { $extracted_str, "var_global" });
			$i += $i1 - 1;
		} else if ($content[$i] == '$') {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1)
				throw("wrong var format");
			array_push($output_arr[$line].$0, { $extracted_str, "var" });
			$i += $i1 - 1;
		} else if ($content[$i] == '@' && $content[$i + 1] == '@') {
			for ($i1 = 2; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1
					|| is_numeric(php_to_string($extracted_str.at(1))))
				throw("wrong function format @$");
			array_push($output_arr[$line].$0,
					{ $extracted_str, "function_self" });
			$i += $i1 - 1;
		} else if (php_to_string($content.at($i)) == "@"
				&& php_to_string($content.at($i + 1)) == "$") {
			for ($i1 = 2; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1
					|| is_numeric(php_to_string($extracted_str.at(1))))
				throw("wrong function format @$");
			array_push($output_arr[$line].$0,
					{ $extracted_str, "function_var" });
			$i += $i1 - 1;
		} else if ($content[$i] == '@' && $content[$i + 1] != '@') {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1
					|| is_numeric(php_to_string($extracted_str.at(1))))
				throw("wrong function format");
			array_push($output_arr[$line].$0, { $extracted_str, "function" });
			$i += $i1 - 1;
		} else if ($content[$i] == '^') {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9-_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (strlen($extracted_str) == 1)
				throw("wrong class format");
			array_push($output_arr[$line].$0, { $extracted_str, "class" });
			$i += $i1 - 1;
		} else if (is_numeric(php_to_string($content.at($i)))) {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[0-9.]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (substr_count($extracted_str, ".") > 1)
				throw("wrong number format, more than 1 point");
			array_push($output_arr[$line].$0, { $extracted_str, "number" });
			$i += $i1 - 1;
		} else if (php_to_string($content.at($i)) == "\"") {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				if (php_to_string($content.at($i + $i1)) == "\""
						&& php_to_string($content.at($i + $i1)) != "\\")
					break;
			}
			$extracted_str = substr($content, $i + 1, $i1 - 1);
// if (strlen ( $extracted_str ) == 1 || is_numeric ( $extracted_str .$1 ))
// throw  ( "wrong string format" );
			array_push($output_arr[$line].$0, { $extracted_str, "string" });
			$i += $i1;
		} else if ($content[$i] == '\'') {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				if (php_to_string($content.at($i + $i1)) == "'"
						&& php_to_string($content.at($i + $i1)) != "\\")
					break;
			}
			$extracted_str = substr($content, $i, $i1 - 1);
// if (strlen ( $extracted_str ) == 1 || is_numeric ( $extracted_str .$1 ))
// throw  ( "wrong string format" );
			array_push($output_arr[$line].$0, { $extracted_str, "string" });
			$i += $i1;
		} else if (is_az(php_to_string($content.at($i)))) {
			for ($i1 = 1; $i1 < $len - $i; $i1++) {
				$matches = php_preg_match("/[a-zA-Z0-9_]/",
						php_to_string($content.at($i + $i1)));
				if (!$matches)
					break;
			}
			$extracted_str = substr($content, $i, $i1);
			if (in_array($extracted_str, __keywords))
				array_push($output_arr[$line].$0,
						{ $extracted_str, "keyword" });
			else if (in_array($extracted_str, __modifiers))
				array_push($output_arr[$line].$0,
						{ $extracted_str, "modifier" });
			else
				array_push($output_arr[$line].$0, { $extracted_str, "string" });
			$i += $i1 - 1;
		} else if (in_array(php_to_string($content.at($i + $i1)),
				__operator_1st_chars)) {
			bool check = false;
			for (auto [$char_count, $operators] : __operators_by_chars_count) {
				for (auto [$key_rtt, $operator] : $operators) {
					if (substr($content, $i, $char_count) == $operator) {
						array_push($output_arr[$line].$0,
								{ substr($content, $i, $char_count), "operator" });
						$i += $char_count - 1;
						check = true;
						break;
					}
					if (check)
						break;
				}
			}
			if (!check)
				array_push($output_arr[$line].$0,
						{ php_to_string($content.at($i)), "other0" });
		} else {
			array_push($output_arr[$line].$0, { php_to_string($content.at($i)),
					"other" });
		}
	}
	for (auto [$i, $output_line] : $output_arr) {
		if (!$output_line.$0.empty())
			$output_arr.erase($i);
	}
	$output_arr = array_values($output_arr);
	return $output_arr;
}
//lll
tokens_line ltrim_arr(tokens_line $arr) {
//	long $k;
	token $v;
	for (auto [$k, $v] : $arr) {
		if (!is_blank_str($v.$0))
			break;
		$arr.erase($k);
	}
	return array_values($arr);
}
bool in_array_lv2_0(string $ele, tokens_line $arr) {
	token $ele_tmp;

	for (auto [$key_rtt, $ele_tmp] : $arr) {
		if ($ele == $ele_tmp.$0)
			return true;
	}
	return false;
}
bool in_array_lv2_1(string $ele, tokens_line $arr) {
	token $ele_tmp;

	for (auto [$key_rtt, $ele_tmp] : $arr) {
		if ($ele == $ele_tmp.$1)
			return true;
	}
	return false;
}
Mixed get_arr_between_brackets_mixed(string $open_bracket,
		Mixed $tokens_line1_arr, long $pos_of_open_bracket) {
	string $close_bracket;
	long $lv;
	long $k;
	token $v;
	//long $pos_of_open_bracket;
	$close_bracket = ")";
	if ($open_bracket == "[")
		$close_bracket = "]";
	$lv = 1;
	for (auto [$k, $v] : $tokens_line1_arr.valueArray) {
		if (stol($k) <= $pos_of_open_bracket)
			continue;
		else if ($v[0] == $open_bracket && $v[1] == "operator")
			$lv++;
		else if ($v[0] == $close_bracket && $v[1] == "operator") {
			$lv--;
			if ($lv == 0)
				break;
		}
	}
	return array_slicem($tokens_line1_arr, $pos_of_open_bracket + 1,
			$k - $pos_of_open_bracket - 1);
}
tokens_line get_arr_between_brackets_tl(string $open_bracket,
		tokens_line $tokens_line1_arr, long $pos_of_open_bracket) {
	string $close_bracket;
	long $lv;
	long $k;
	token $v;
	//long $pos_of_open_bracket;
	$close_bracket = ")";
	if ($open_bracket == "[")
		$close_bracket = "]";
	$lv = 1;
	for (auto [$k, $v] : $tokens_line1_arr) {
		if ($k <= $pos_of_open_bracket)
			continue;
		else if ($v.$0 == $open_bracket && $v.$1 == "operator")
			$lv++;
		else if ($v.$0 == $close_bracket && $v.$1 == "operator") {
			$lv--;
			if ($lv == 0)
				break;
		}
	}
	return array_slice($tokens_line1_arr, $pos_of_open_bracket + 1,
			$k - $pos_of_open_bracket - 1);
}
arr_ll find_all_token_at_level0_by_type(string $token_type_to_compare,
		tokens_line $tokens_line1_arr) {
	long $lv1;
	long $lv2;
	arr_ll $return;
	//long $k;
	token $token;
	$lv1 = $lv2 = 0;
	$return = { };
	for (auto [$k, $token] : $tokens_line1_arr) {
//		if (!is_token($token)) {
//			continue;
//		}
		if ($token.$0 == "(" && $token.$1 == "operator") {
			$lv1++;
		} else if ($token.$0 == "[" && $token.$1 == "operator") {
			$lv2++;
		} else if ($token.$0 == ")" && $token.$1 == "operator") {
			$lv1--;
		} else if ($token.$0 == "]" && $token.$1 == "operator") {
			$lv2--;
		} else if ($token.$1 == $token_type_to_compare && $lv1 == 0
				&& $lv2 == 0) {
			array_push($return, $k);
		}
	}
	return $return;
}
//struct name_and_params {
//public:
//	string name;
//	arr_lm params;
//	name_and_params() {
//		this->name = "";
//		this->params = { };
//	}
//};
struct two_sides {
public:
	;
	tokens_line $0;
	tokens_line $1;
	two_sides() {
		this->$0 = { };
		this->$1 = { };
	}
};
tokens_line_arr array_cut_by_pos(tokens_line $arr, arr_ll $positions) {
	tokens_line_arr $return;
	long $i = 0;
	long $pos;
	long $start;
	long $stop;
	long $len;
	if ($positions.empty()) {
		return { {0,$arr
			}};
	}
	;
	$return = { };
	for (auto [$i, $pos] : $positions) {
		if (isset($positions, $i - 1))
			$start = $positions[$i - 1] + 1;
		else
			$start = 0;
		if (isset($positions, $i))
			$stop = $pos;
		else
			$stop = sizeof($arr);
		$len = $stop - $start;
		$return[$i] = array_slice($arr, $start, $len);
	}

	$return[$i + 1] = array_slice($arr, $pos + 1, sizeof($arr));
	return $return;
}
arr_ll find_all_token_at_level0(token $token_to_compare,
		tokens_line $tokens_line1_arr) {
	long $lv1;
	long $lv2;
	arr_ll $return;
//	long $k;
	//token $token;
	$lv1 = $lv2 = 0;
	$return = { };
	for (auto [$k, $token] : $tokens_line1_arr) {
//		if (!is_token($token)) {
//			continue;
//		}
		if ($token.$0 == "(" && $token.$1 == "operator") {
			$lv1++;
		} else if ($token.$0 == "[" && $token.$1 == "operator") {
			$lv2++;
		} else if ($token.$0 == ")" && $token.$1 == "operator") {
			$lv1--;
		} else if ($token.$0 == "]" && $token.$1 == "operator") {
			$lv2--;
		} else if ((token) $token == $token_to_compare && $lv1 == 0
				&& $lv2 == 0) {
			array_push($return, $k);
		}
	}
	return $return;
}
Mixed get_function_and_params_lv0(tokens_line $tokens_line1_arr) {
	Mixed $return;
	arr_ll $all_func_names_pos;
	tokens_line_arr $two_sides;
	tokens_line_arr $tmp_array;
	arr_ll $left_comma_pos;
	arr_ll $right_comma_pos;
	tokens_line $v;
	$return = Mixed();
	$all_func_names_pos = find_all_token_at_level0_by_type("function",
			$tokens_line1_arr);
	if (sizeof($all_func_names_pos) != 1)
		return Mixed();
	$return.push("name", $tokens_line1_arr[$all_func_names_pos[0]].$0);
	$two_sides = array_cut_by_pos($tokens_line1_arr, $all_func_names_pos);
	$tmp_array = { };
	$left_comma_pos = find_all_token_at_level0( { ",", "operator" },
			$two_sides[0]);
	$tmp_array = array_cut_by_pos($two_sides[0], $left_comma_pos);
	$right_comma_pos = find_all_token_at_level0( { ",", "operator" },
			$two_sides[1]);
	$tmp_array = array_merge($tmp_array,
			array_cut_by_pos($two_sides[1], $right_comma_pos));
	for (auto [$key_rtt, $v] : $tmp_array) {
		if ($v.empty())
			$return["params"].push(parse_expression($v));
	}
	return $return;
}
struct getline_subblock_t {
public:
	long i;
	tokens_line1_arr arr;
	getline_subblock_t() {
		this->i = 0;
		this->arr = { };
	}
};
getline_subblock_t getline_subblock(tokens_line1_arr $tokens_line1_arr,
		long $header_line_i) {
	long $header_lv;
	tokens_line1_arr $tmp_arr;
	long $i;
	tokens_line1 $v;
	getline_subblock_t _return = getline_subblock_t();
	$header_lv = $tokens_line1_arr[$header_line_i].$1;
	$tmp_arr = array_slice($tokens_line1_arr, $header_line_i);
	$tmp_arr = array_values($tmp_arr);
	$i = 0;
	for ($i = 0; $i < (long) sizeof($tmp_arr) - 1; $i++) {
		$v = $tmp_arr[$i + 1];
		if ($v.$1 <= $header_lv) {
			_return.i = $i;
			_return.arr = array_slice($tokens_line1_arr, $header_line_i + 1,
					$i);
			return _return;
		}
	}
	_return.i = $i;
	_return.arr = array_slice($tokens_line1_arr, $header_line_i + 1);
	return _return;;
}
Mixed parse_array_element(tokens_line $tokens_line1_arr) {
	tokens_line_arr $tmp_arr;
	arr_ll $all_marks_pos;
	$tmp_arr = { };
	$all_marks_pos = find_all_token_at_level0(token("=>", "operator"),
			$tokens_line1_arr);
	$tmp_arr = array_cut_by_pos($tokens_line1_arr, $all_marks_pos);
	Mixed _return;
	if (sizeof($tmp_arr) > 2 || sizeof($tmp_arr) < 1)
		throw("Invalid array declaration.");
	else if (sizeof($tmp_arr) == 1) {
		_return.push("key", "NULL");
		_return.push("value", parse_expression($tmp_arr[0]));
		return _return;
	} else if (sizeof($tmp_arr) == 2) {
		_return.push("key", parse_expression($tmp_arr[0]));
		_return.push("value", parse_expression($tmp_arr[1]));
		return _return;
	}
	return _return;
}
Mixed parse_array(tokens_line $tokens_line1_arr) {
	arr_ll $all_commas;
	tokens_line_arr $elements;
	Mixed $return;
	tokens_line_arr $element;
	$all_commas = find_all_token_at_level0( { ",", "operator" },
			$tokens_line1_arr);
	$elements = array_cut_by_pos($tokens_line1_arr, $all_commas);
	for (auto [$key_rtt, $element] : $elements) {
		$return.push(parse_array_element($element));
	}
	$return.push("type", "array");
	$return.push("body", $return);
	return $return;
}
//function is_token($input) {
//if (isset($input[0]) && isset($input[1]) && sizeof($input) == 2)
//return true;
//return false;
//}
tokens_line remove_all_spaces(tokens_line $tokens_line1_arr) {
	tokens_line $return;
	token $ele;
	$return = { };
	for (auto [$key_rtt, $ele] : $tokens_line1_arr) {
		// if (! is_token ( $tokens_arr ))
		// continue;
		if ($ele.$1 != "spaces")
			array_push($return, $ele);
	}
	return $return;
}
Mixed parse_var(tokens_line $tokens_line1_arr) {
	tokens_line $tokens_arr1;
	long $lv;
	tokens_line_arr $tmp;
	token $token;
	$tokens_line1_arr = remove_all_spaces($tokens_line1_arr);
	if ($tokens_line1_arr[0].$1 != "var"
			&& $tokens_line1_arr[0].$1 != "var_global")
		throw("not a var");
	$tokens_arr1 = array_slice($tokens_line1_arr, 1);
	$lv = 0;
// $tmp = Mixed();
	for (auto [$key_rtt, $token] : $tokens_arr1) {
		if ($token == token("[", "operator")) {
			$lv++;
		} else if ($token == token("]", "operator")) {
			$lv--;
		} else if ($lv == 0)
			throw("not valid var");
	}
	return parse_expression($tokens_line1_arr);
}
Mixed parse_complex_var(tokens_line $tokens_line1_arr) {
	arr_ll $all_dots_pos;
	tokens_line_arr $cutted;
	tokens_line $var;
	$all_dots_pos = find_all_token_at_level0( { ".", "operator" },
			$tokens_line1_arr);
	$cutted = array_cut_by_pos($tokens_line1_arr, $all_dots_pos);
	for (auto [$key_rtt, $var] : $cutted) {
		try {
			parse_var($var);
		} catch (...) {
			return Mixed();
		}
	}
	return parse_expression($tokens_line1_arr);
}
Mixed process_assignment(tokens_line $tokens_line1_arr) {
	arr_ll $pos_of_all_colon;
	Mixed $return, _return1, _return2;
	tokens_line_arr $tmp_arr;
	tokens_line $value;
	tokens_line $tmp_ele;
	long $post_of_1st_colon;
	tokens_line $left;
	tokens_line $right;
	arr_ll $left_commas_lv0;
	arr_ll $right_commas_lv0;
	Mixed $tmp;
	tokens_line_arr $left_slided;
	tokens_line_arr $right_slided;
//	long $i;
	Mixed $one_var;
	tokens_line $one_value;
	$tokens_line1_arr = remove_all_spaces($tokens_line1_arr);
	$pos_of_all_colon = find_all_token_at_level0( { ":", "operator" },
			$tokens_line1_arr);
	if (sizeof($pos_of_all_colon) == 0) {
		return Mixed(false);
	} else if (sizeof($pos_of_all_colon) > 1) {
		$tmp_arr = array_cut_by_pos($tokens_line1_arr, $pos_of_all_colon);
		$value = array_pop($tmp_arr);
		for (auto& [$key_rtt, $tmp_ele] : $tmp_arr) {
			array_push($tmp_ele, token(":", "operator"));
			$tmp_ele = array_merge($tmp_ele, $value);
			$return.push(process_assignment($tmp_ele));
		}
		_return1.push("type", "inline_block");
		_return1.push("body", $return);
		return _return1;
	}
	$post_of_1st_colon = $pos_of_all_colon[0];
	$left = array_slice($tokens_line1_arr, 0, $post_of_1st_colon);
	$right = array_slice($tokens_line1_arr, $post_of_1st_colon + 1);
	$left_commas_lv0 = find_all_token_at_level0( { ",", "operator" }, $left);
	$right_commas_lv0 = find_all_token_at_level0( { ",", "operator" }, $right);
	if (sizeof($left_commas_lv0) != sizeof($right_commas_lv0))
		throw("not valid assignment size");
	if ($left_commas_lv0.empty()) {
		$tmp = parse_expression($right);
		_return1.push("type", "assignment");
		_return1.push("left", parse_complex_var($left));
		_return1.push("right", $tmp);
		_return1.push("return", $tmp);
		return _return1;
	} else {
		$left_slided = array_cut_by_pos($left, $left_commas_lv0);
		$right_slided = array_cut_by_pos($right, $right_commas_lv0);
		Mixed _return1;
		for (auto [$i, $one_var] : $left_slided) {
			$one_value = $right_slided[$i];
			Mixed $return;
			$return.push("type", "assignment");
			$return.push("left", parse_complex_var($one_var));
			$return.push("right", parse_expression($one_value));
			_return1.push($return);
		}
		_return2.push("type", "inline_block");
		_return2.push("body", $return);
		return _return2;
	}
}
struct operator1 {
public:
	long $0;
	string $1;
	operator1() {
		this->$0 = 0;
		this->$1 = "";
	}
	operator1(long _long, string _string) {
		this->$0 = _long;
		this->$1 = _string;
	}
};
typedef map<long, operator1> arr_lo1;
Mixed process_multiple_operators(tokens_line $tokens_line1_arr) {
	arr_lo1 $arr_operators;
//	long $k;
	tokens_line $tokens_arr_tmp;
	token $token;
	long $min;
	long $highest_operator_pos;
	string $highest_operator;
	token $operator;
	Mixed $return, _tmp, _tmp1;
	while (true) {
		$arr_operators = { };
		for (auto [$k, $token] : $tokens_line1_arr) {
			if ($token.$1 == "operator") {
				array_push($arr_operators, operator1($k, $token.$0));
			}
		}
		if (sizeof($arr_operators) == 1) {
			_tmp.push("type", "expr");
			_tmp.push("body",
					tokens_arr_to_name_and_type_format($tokens_line1_arr));
			return _tmp;
		}
		$min = 30;
		$highest_operator_pos = 0;
		$highest_operator = "";
		for (auto [$key_rtt, $operator] : $arr_operators) {
			if (__real_operators[$operator.$1][1] < $min) {
				$highest_operator_pos = $operator.$0;
				$highest_operator = $operator.$1;
				$min = __real_operators[$operator.$1][1];
			}
		}
		if (__real_operators[$highest_operator][0] == 0) {
			$return = array_slice($tokens_line1_arr, 0, $highest_operator_pos);
			_tmp.push("type", "expr");
			_tmp1.push(0, $tokens_line1_arr[$highest_operator_pos]);
			_tmp1.push(1, $tokens_line1_arr[$highest_operator_pos + 1]);
			_tmp.push("body", _tmp1);
			$tokens_arr_tmp = array_slice($tokens_line1_arr,
					$highest_operator_pos + 2, sizeof($tokens_line1_arr));
			$return = array_merge($return, $tokens_arr_tmp);
		} else if (__real_operators[$highest_operator][0] == 1) {
			$return = array_slice($tokens_line1_arr, 0,
					$highest_operator_pos - 1);
			_tmp = Mixed();
			_tmp.push("type", "expr");
			_tmp1 = Mixed();
			_tmp1.push(0, $tokens_line1_arr[$highest_operator_pos - 1]);
			_tmp1.push(1, $tokens_line1_arr[$highest_operator_pos]);
			_tmp.push("body", _tmp1);
			$return.push(_tmp);
			$tokens_arr_tmp = array_slice($tokens_line1_arr,
					$highest_operator_pos + 1, sizeof($tokens_line1_arr));
			$return = array_merge($return, $tokens_arr_tmp);
		} else if (__real_operators[$highest_operator][0] == 2) {
			$return = array_slice($tokens_line1_arr, 0,
					$highest_operator_pos - 1);
			_tmp = Mixed();
			_tmp.push("type", "expr");
			_tmp1 = Mixed();
			_tmp1.push(0, $tokens_line1_arr[$highest_operator_pos - 1]);
			_tmp1.push(1, $tokens_line1_arr[$highest_operator_pos]);
			_tmp1.push(1, $tokens_line1_arr[$highest_operator_pos + 1]);
			_tmp.push("body", _tmp1);
			$return.push(_tmp);
			$return = array_merge($return,
					array_slice($tokens_line1_arr, $highest_operator_pos + 2));
		}
		$tokens_line1_arr = $return;
	}
	_tmp = Mixed();
	_tmp.push("type", "expr");
	_tmp.push("body", tokens_arr_to_name_and_type_format($return));
	return _tmp;
}
bool is_new_clause(tokens_line $tokens_line1_arr) {
	token $token;
	$tokens_line1_arr = remove_all_spaces($tokens_line1_arr);
	if (sizeof($tokens_line1_arr) < 2)
		return false;
	for (auto [$key_rtt, $token] : $tokens_line1_arr) {
		if ($token.$0 == "new" && $token.$1 == "keyword")
			return true;
	}
	return false;
}
Mixed tokens_arr_trim1(Mixed $tokens_line1_arr) {
	//reset($tokens_arr);
	if (isset($tokens_line1_arr, sizeof($tokens_line1_arr) - 1)
			&& $tokens_line1_arr[(long) sizeof($tokens_line1_arr) - 1][1l]
					== "spaces")
		array_pop_nr($tokens_line1_arr);
	if (isset($tokens_line1_arr, 0l) && $tokens_line1_arr[0][1] == "spaces") {
		array_shift_nr($tokens_line1_arr);
//		reset($tokens_arr);
	}
	return $tokens_line1_arr;
}
Mixed tokens_arr_trim(Mixed $tokens_line1_arr) {
	Mixed $token_array_trimmed;
	$token_array_trimmed = $tokens_line1_arr;
	$token_array_trimmed = tokens_arr_trim1($tokens_line1_arr);
	while (sizeof($tokens_line1_arr) > sizeof($token_array_trimmed)) {
		$tokens_line1_arr = $token_array_trimmed;
		$token_array_trimmed = tokens_arr_trim1($tokens_line1_arr);
	}
	return $token_array_trimmed;
}
Mixed convert_spaces_to_concat_operators(Mixed $tokens_line1_arr) {
	arr_ll $spaces_poses;
	Mixed $return;
//	long $pos;
	token $token;
	string $type;
	string $name;
	long $spaces_pos;
	Mixed $before;
	Mixed $after;
	string $before_type;
	string $after_type;
	arr_ls $concat_types;
	$tokens_line1_arr = tokens_arr_trim($tokens_line1_arr);
// $spaces_poses = find_all_token_at_level0_by_type ( "spaces", $tokens_arr );
	for (auto [$pos, $token] : $tokens_line1_arr.valueArray) {
		$type = (string) $token[1];
		if ($type != "spaces") {
			$return.push($token);
			continue;
		}
		$name = (string) $token[0];
		$spaces_pos = stoi((string) $pos);
		$before = $tokens_line1_arr[$spaces_pos - 1];
		$after = $tokens_line1_arr[$spaces_pos + 1];
		$before_type = (string) $before[1];
		$after_type = (string) $after[1];
		$concat_types = { { 0, "var" }, { 1, "number" }, { 2, "string" } };
		if (in_array($before_type, $concat_types)
				&& in_array($after_type, $concat_types)) {
			$return.push(".", "operator");
			$return.push($name, "string");
			$return.push(".", "operator");
		}
	}
	return $return;
}
token token_to_name_and_type_format(Mixed $token) {
	// if (! is_token ( $token ))
	// return $token;
	return token($token.$0, $token.$1);
}

Mixed parse_expression(Mixed $tokens_line1_arr) {
	Mixed $complex_expr_arr;
	token $first_token;
	bool $is_complex_expr;
//	long $k;
	token $token;
	Mixed $result_arr;
	Mixed $parsed;
	Mixed $function_and_params;
	string $function_name;
	Mixed $function_args;
	long $operators_count;
	tokens_line $tokens_arr1;
//	long $j;
	Mixed $return, _return, _return1;
	arr_ls $classes;
//	long $l;
	Mixed $param;
	string $type;
	string $name;
	if ($tokens_line1_arr["type"] == "expr")
		$tokens_line1_arr = (Mixed) $tokens_line1_arr["data"];
	$complex_expr_arr = Mixed();
//	reset($tokens_arr);
	$tokens_line1_arr = tokens_arr_trim1($tokens_line1_arr);
	if (sizeof($tokens_line1_arr) == 1) {
		if (is_token(get_1st_ele($tokens_line1_arr))) {
			if (in_array((string) get_1st_ele($tokens_line1_arr)[1], { { 0,
					"string" }, { 1, "number" }, { 2, "var" }, { 3, "class" }, {
					4, "array" }, { 5, "expr" } })) {
				$first_token = reset($tokens_line1_arr);
				$return.push("type", $first_token.$1);
				$return.push("name", $first_token.$0);
				return $return;
			}
		} else {
			return get_1st_ele($tokens_line1_arr);
		}
	}
	$is_complex_expr = false;
	for (long $k = 0l; $k < (long) sizeof($tokens_line1_arr); $k++) {
		$token = $tokens_line1_arr[$k];
		if ($token.$0 != "") {
			$complex_expr_arr.push((Mixed) $token);
			continue;
		}
		if ($token.$0 == "(" && $token.$1 == "operator") {
			$is_complex_expr = true;
			$result_arr = get_arr_between_brackets_mixed("(", $tokens_line1_arr,
					$k);
			$complex_expr_arr.push(parse_expression($result_arr));
			$k += sizeof($result_arr) + 1;
		} else if ($token.$0 == "[" && $token.$1 == "operator") {
			$is_complex_expr = true;
			$result_arr = get_arr_between_brackets_mixed("[", $tokens_line1_arr,
					$k);
			$complex_expr_arr.push(parse_array($result_arr.to_tokens_line()));
			$k += sizeof($result_arr) + 1;
		} else if ($token.$0 == ")" && $token.$1 == "operator") {
			throw("not valid close round bracket");
		} else if ($token.$0 == "]" && $token.$1 == "operator") {
			throw("not valid close square bracket");
		} else {
			$complex_expr_arr.push($token);
		}
	}
	mixed_to_tokens_line_with_place_holders_rs complex_tokens_line_rs =
			mixed_to_tokens_line_with_place_holders($complex_expr_arr);
	tokens_line complex_tokens_line = complex_tokens_line_rs.$0;
	map<string, Mixed> _map_placeholders = complex_tokens_line_rs.$1;
	if ($is_complex_expr) {
		$parsed = parse_expression($complex_expr_arr);
		if (in_array($parsed["type"], { { 0, "array" }, { 1, "expr" }, { 2,
				"assignment" }, { 3, "function" } }))
			return replace_placeholders_recruisively($parsed, _map_placeholders);
		else {
			_return.push("type", "expr");
			_return.push("body", _return1);
			return replace_placeholders_recruisively(_return, _map_placeholders);
		}
	}
// assignment expr
	for (auto [$k, $token] : $tokens_line1_arr.valueArray) {
		if ($token[0] == ":" && $token[1] == "operator") {
			_return = process_assignment(complex_tokens_line);
			return replace_placeholders_recruisively(_return, _map_placeholders);
		}
	}
// simple function $function_and_params = get_function_and_params_lv0($tokens_arr);
	if (!$function_and_params.valueArray.empty()
			&& isset($function_and_params, "name")) {
		$function_name = (string) $function_and_params["name"];
		$function_args = $function_and_params["params"];
		_return.push("type", "function");
		_return.push("name", $function_name);
		_return.push("args", $function_args);
		return replace_placeholders_recruisively(_return, _map_placeholders);
	}
// multiple operator but no brackets expr
	$tokens_line1_arr = convert_spaces_to_concat_operators($tokens_line1_arr);
	$operators_count = 0;
	for (auto [$key_rtt, $token] : complex_tokens_line) {
		if ($token.$1 == "operator")
			$operators_count++;
	}
	if ($operators_count > 1) {
		_return = process_multiple_operators(complex_tokens_line);
		return replace_placeholders_recruisively(_return, _map_placeholders);
	}
// new object of class
	if (is_new_clause(complex_tokens_line)) {
//		$tokens_arr1 = $tokens_arr;
		for (auto [$j, $token] : complex_tokens_line) {
			if ($token.$0 == "new" && $token.$1 == "keyword")
				$tokens_arr1[(long) $j] = token("@new", "function");
		}
		$return = get_function_and_params_lv0(complex_tokens_line);
		$classes = { };
		for (auto [$l, $param] : $return["params"].valueArray) {
			if (isset($param, "type"))
				$type = (string) (Mixed) (*$param)["type"];
			else
				$type = (string) (Mixed) (*$param)[1];
			if ($type == "class") {
				if (isset($param, "name"))
					$type = (string) (Mixed) (*$param)["name"];
				else
					$type = (string) (Mixed) (*$param)[0];
				array_push($classes, $name);
				$return["params"].valueArray.erase($l);
			}
		}
		if (sizeof($classes) != 1)
			throw("new but no/multi class");
		reset($return["params"]);
		$return.push("type", "new");
		$return.push("class", $classes[0]);
		$return.push("params", $return["params"]);
		return $return;
	}
// simple single operator expr
	$return.push("type", "expr");
	$return.push("body", tokens_arr_to_name_and_type_format($tokens_line1_arr));
	return $return;
}
Mixed parse_expression(tokens_line $tokens_line1_arr) {
	return parse_expression(Mixed($tokens_line1_arr));
}
Mixed structurelize(tokens_line1_arr _arr);
Mixed process_if(long &$line_num, tokens_line1_arr $tokens_line1_arr) {
	tokens_line $if_line;
	getline_subblock_t $getline_subblock;
	map<long, tokens_line1_arr> $if_blocks;
	map<long, Mixed> $if_conditions;
	tokens_line1_arr $else_block;
	Mixed $return, _tmp;

	$if_line = $tokens_line1_arr[$line_num].$0;
	$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
	$line_num += $getline_subblock.i;
	array_push($if_blocks, $getline_subblock.arr);
	array_push($if_conditions, parse_expression(array_slice($if_line, 1)));
	while (true) {
		if (isset($tokens_line1_arr[$line_num + 1], 0)
				&& $tokens_line1_arr[$line_num + 1].$0[0].$0 == "else if"
				&& $tokens_line1_arr[$line_num + 1].$0[0].$1 == "keyword") {
			$line_num++;

			$if_line = $tokens_line1_arr[$line_num].$0;
			$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
			$line_num += $getline_subblock.i;
			array_push($if_blocks, $getline_subblock.arr);
			array_push($if_conditions,
					parse_expression(array_slice($if_line, 1)));
		} else {
			break;
		}
	}
	if ($tokens_line1_arr[$line_num + 1].$0[0].$0 == "else"
			&& $tokens_line1_arr[$line_num + 1].$0[0].$1 == "keyword"
			&& sizeof($tokens_line1_arr[$line_num + 1].$0) == 1) {
		$line_num++;
		$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
		$line_num += $getline_subblock.i;
		$else_block = $getline_subblock.arr;
	} else {
		$else_block = { };
		$return.push("type", "ifs");
		$return.push("ifs", Mixed());
		for (unsigned long k = 0; k < $if_blocks.size(); k++) {
			_tmp = Mixed();
			_tmp.push("condition", $if_conditions[k]);
			_tmp.push("body", structurelize($if_blocks[k]));
			$return["ifs"].push(to_string(k), _tmp);
		}
		$return.push("else", structurelize($else_block));
		return $return;
	}
	return $return;
}
Mixed for_parse(tokens_line $for_tokens) {
//	long $_time;
	Mixed $return;
//	echo("");
	if ($for_tokens[2].$1 == "number" && isset($for_tokens, 4)
			&& $for_tokens[4].$1 == "var"
			&& array_search(token(",", "operator"), $for_tokens) == false) {
		$return.push(tokenize($for_tokens[4].$0 + ":1")[0].$0);
		$return.push(
				tokenize($for_tokens[4].$0 + "<=" + $for_tokens[2].$0)[0].$0);
		$return.push(tokenize($for_tokens[4].$0 + "++")[0].$0);
		return $return;
	} else if (isset($for_tokens, 4) && $for_tokens[2].$1 == "number"
			&& $for_tokens[4].$0 == "times" && $for_tokens[4].$1 == "keyword")
		$return.push(tokenize("$_time:1")[0].$0);
	$return.push(tokenize("$_time<=" + $for_tokens[2].$0)[0].$0);
	$return.push(tokenize("$_time++")[0].$0);
	return $return;
	array_shift($for_tokens);
	$return = explode_tokens(token(",", "operator"), $for_tokens);
	if (sizeof($return) != 3)
		throw("invalid for line");
	return $return;
}
Mixed foreach_parse(tokens_line $foreach_tokens) {
	Mixed $return, _return1, _return2;
	string $_k;
	string $_v;
	array_shift($foreach_tokens);
	$return = explode_tokens(",", $foreach_tokens);
	if (sizeof($return) == 3)
		return $return;
	if (sizeof($return) == 2) {
		_return1.push("0", "$_k");
		_return1.push("1", "var");
		$return.push(2, $return[1]);
		$return[1] = _return1;
		return $return;
	}
	if (sizeof($return) == 1) {
		_return1.push("0", "$_k");
		_return1.push("1", "var");
		$return.push("1", _return1);
		_return2.push("0", "$_v");
		_return2.push("1", "var");
		$return.push("2", _return2);
		return $return;
	}
	return $return;
}
Mixed process_for(long &$line_num, tokens_line1_arr $tokens_line1_arr) {
	tokens_line $for_line;
	getline_subblock_t $getline_subblock;
	tokens_line1_arr $for_block;
	Mixed $for_parse;
	Mixed $return;
	$for_line = $tokens_line1_arr[$line_num].$0;
	$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
	$line_num += $getline_subblock.i;
	$for_block = $getline_subblock.arr;
	$for_parse = for_parse($for_line);
	$return.push("type", "for");
	$return.push("init", parse_expression($for_parse[0]));
	$return.push("increment", parse_expression($for_parse[2]));
	$return.push("terminate", parse_expression($for_parse[1]));
	$return.push("body", structurelize($for_block));
	return $return;
}
Mixed process_while(long $line_num, tokens_line1_arr $tokens_line1_arr) {
	tokens_line $while_line;
	Mixed $return;
//	long $while_lv;
	tokens_line1_arr $while_block;
	getline_subblock_t $getline_subblock;
	Mixed $for_parse;
	$while_line = $tokens_line1_arr[$line_num].$0;
// $while_lv = $tokens_arr [$line_num] .$1;
	$while_block = { };
	$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
	$line_num += $getline_subblock.i;
	$while_block = $getline_subblock.arr;
// $for_parse = for_parse ( array_slice ( $while_line, 0, sizeof ( $while_line ) ) );
	$return.push("type" "while");
	$return.push("condition", parse_expression(array_slice($while_line, 1)));
	$return.push("body", structurelize($while_block));
	return $return;
}
Mixed is_function_def(tokens_line $tokens) {
	bool $check;
	token $token;
	Mixed $function_name;
	Mixed $function_vars;
	long $function_vars_i;
	long $i;
	Mixed $vars1, $return, _return1;
	tokens_line $arr_between_brackets;
//	long $k;
	tokens_line $vars;
	Mixed $value_tokens;
	Mixed $value_expr;
	if ($tokens[sizeof($tokens) - 1].$0 != ":"
			|| $tokens[sizeof($tokens) - 1].$1 != "operator")
		return false;
	$check = false;
// /================
	for (auto [$key_rtt, $token] : $tokens) {
		if ($token.$1 == "function") {
			$check = true;
			break;
		}
	}
	if ($check == false)
		return false;
// =================
	array_pop($tokens);
	$function_name = "";
	$function_vars = Mixed();
	$function_vars_i = 0;
	for ($i = 0; $i < count($tokens); $i++) {
		$token = $tokens[(long) $i];
		if ($token.$1 == "function")
			if ($function_name == "") {
				$function_name = $token.$0;
				if ((int) $function_vars_i > 0)
					$function_vars_i++;
			} else
				throw("function declare has multiple name");
// else if ($token .$1 != "var" && $token .$1 != "spaces" && $token .$0 != ",")
// throw  ( "non-var not allowed function declare" );
		else if ($token.$1 == "var") {
			$function_vars[$function_vars_i].push($token);
		} else if ($token.$0 == "[" && $token.$1 == "operator") {
			$arr_between_brackets = get_arr_between_brackets_tl("[", $tokens,
					$i);
			$function_vars[$function_vars_i].push(
					parse_expression($arr_between_brackets));
			$i += sizeof($arr_between_brackets);
		} else if ($token.$0 == "(" && $token.$1 == "operator") {
			$arr_between_brackets = get_arr_between_brackets_tl("(", $tokens,
					$i);
			$function_vars[$function_vars_i].push(
					parse_expression($arr_between_brackets));
			$i += sizeof($arr_between_brackets);
		} else if ($token.$0 == "," && $token.$1 == "operator") {
			$function_vars_i++;
			$function_vars[$function_vars_i] = Mixed();
		} else {
// $function_vars_i ++;
			$function_vars[$function_vars_i].push($token);
		}
	}
	if ($function_vars.valueArray.empty())
		$function_vars = Mixed();
// validate function_vars
	for (auto& [$k, $vars] : $function_vars.valueArray) {
		$vars1 = Mixed();
		$function_vars[$k] = remove_spaces_from_tokens_arr($vars);
		$vars1 = $function_vars[$k];
		if (sizeof($vars1) == 2)
			throw("function declare invalid arg");
		if ((string) $vars1[0][1] != "var")
			throw("function declare no var");
		if (sizeof($vars1) >= 3
				&& ((string) $vars1[1][0] != ":"
						|| (string) $vars1[1][1] != "operator"))
			throw("function var declare no :");
		$value_tokens = array_slicem($vars1, 2);
		$value_expr = parse_expression($value_tokens);
		_return1.push(0, $vars1[0][0]);
		$function_vars.push($k, _return1);
		if (sizeof($vars1) >= 3)
			$function_vars[$k].push(1, $value_expr);
	}
	$return.push($function_name);
	$return.push($function_vars);
	return $return;
}
tokens_line is_list(tokens_line $tokens, arr_ls $types, token $delimiter =
		token(",", "operator")) {
	tokens_line $return;
	bool $is_delimiter;
	token $token;
	Mixed _return1;
	$is_delimiter = true;
	for (auto [$key_rtt, $token] : $tokens) {
		$is_delimiter = !$is_delimiter;
		if ($is_delimiter) {
			if (!($token == $delimiter)) {
				return tokens_line();
			}
		} else {
			if (!in_array($token.$1, $types))
				return tokens_line();
			array_push($return, $token);
		}
	}
	return $return;
}
tokens_line is_list(tokens_line $tokens, string $type,
		token $delimiter = token(",", "operator")) {
	return is_list($tokens, { { 0, $type } }, $delimiter);
}
arr_ls get_each_element_from_array(tokens_line $arr, long $num = 1) {
	arr_ls $return;
//	long $k;
	token $token;
	$return = { };
	for (auto [$k, $token] : $arr) {
		if ($num == 0) {
			$return[$k] = ((token) $token).$0;
		} else if ($num == 1) {
			$return[$k] = ((token) $token).$1;
		}
	}
	return $return;
}
Mixed is_class_def(tokens_line $tokens) {
	Mixed $return;
	long $last_token_i;
	tokens_line $list;
	$return.push("class", "");
	$return.push("extends", Mixed());
	$tokens = remove_all_spaces($tokens);
	$last_token_i = sizeof($tokens) - 1;
	if (!isset($tokens, 0) || $tokens[0].$1 != "class")
		return Mixed();
	if ($tokens[$last_token_i].$0 != ":"
			|| $tokens[$last_token_i].$1 != "operator")
		return Mixed();
// /================
	if (sizeof($tokens) == 2) {
		$return["class"] = $tokens[0].$0;
		return $return;
	} else if (sizeof($tokens) < 2 || sizeof($tokens) == 3) {
		return false;
	} else if ($tokens[1].$0 != "<<" || $tokens[1].$1 != "operator") {
		return false;
	} else if (!($list = is_list(array_slice($tokens, 2, $last_token_i - 2),
			"class")).empty()) {
		return false;
	} else {
		$return["class"] = $tokens[0].$0;
		$return["extends"] = get_each_element_from_array($list, 0);
		return $return;
	}
	return false;
}
Mixed process_function_def(long $line_num, tokens_line1_arr $tokens_line1_arr,
		Mixed $func_declare, bool $is_method = false) {
	getline_subblock_t $getline_subblock;
	tokens_line1_arr $func_def_block;
	Mixed $return, _tmp;
	$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
	$line_num += $getline_subblock.i;
	$func_def_block = $getline_subblock.arr;
	if (!$is_method) {
		_tmp.push("type", "func_def");
		_tmp.push("name", $func_declare[0]);
		_tmp.push("vars", $func_declare[1]);
		_tmp.push("body", structurelize($func_def_block));
		__funcs.push(_tmp);
		return Mixed();
	} else {
		$return.push("type", "func_def");
		$return.push("name", $func_declare[0]);
		$return.push("vars", $func_declare[1]);
		$return.push("body", structurelize($func_def_block));
		return $return;
	}
}
Mixed parse_property(tokens_line $tokens_line1_arr) {
	arr_ls $modifiers;
	long $start_vars_section;
	Mixed $return;
//	long $i;
	token $token;
	tokens_line $vars_section;
	arr_ll $all_colons;
	tokens_line_arr $two_sides;
	Mixed _tmp;
	tokens_line $list_vars;
	Mixed $var;
	arr_ll $commas_pos;
	Mixed $values_arr;
	tokens_line $values_tokens;
	string $vars;
	try {
		$tokens_line1_arr = remove_all_spaces($tokens_line1_arr);
		$modifiers = { };
		$start_vars_section = -1;
		$return = Mixed();
		for (auto [$i, $token] : $tokens_line1_arr) {
			if ($token.$1 == "modifier") {
				array_push($modifiers, $token.$0);
			} else {
				$start_vars_section = $i;
				break;
			}
		}
		if ($modifiers.empty())
			$modifiers = { { 0, "public" } };
		if ($start_vars_section == -1)
			throw("non-var in property");
		$vars_section = array_slice($tokens_line1_arr, $start_vars_section);
		$all_colons = find_all_token_at_level0(token(":", "operator"),
				$vars_section);
		if (sizeof($all_colons) > 1) {
			throw("too many colons in property");
		} else if (sizeof($all_colons) == 1) {
			$two_sides = array_cut_by_pos($vars_section, $all_colons);
			if (sizeof(find_all_token_at_level0(token(",", "operator"),
					$two_sides[0]))
					!= sizeof(find_all_token_at_level0(token(",", "operator"),
							$two_sides[1])))
				throw("colons count not balance in property");
			if (!($list_vars = is_list($two_sides[0], "var")).empty()) {
				for (auto [$key_rtt, $var] : $list_vars) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", $var.$0);
					_tmp.push("modifiers", $modifiers);
					$return.push(_tmp);
				}
			} else {
				throw("not valid property declare");
			}
			// ======================
			$commas_pos = find_all_token_at_level0(token(",", "operator"),
					$two_sides[1]);
			$values_arr = array_cut_by_pos($two_sides[1], $commas_pos);
			for (auto [$i, $values_tokens] : $values_arr.valueArray) {
				$return[stol($i)]["value"] = parse_expression($values_tokens);
			}
			// ======================
			return $return;
		} else {
			if (!($list_vars = is_list($vars_section, "var")).empty()) {
				for (auto [$key_rtt, $var] : $list_vars) {
					_tmp = Mixed();
					_tmp.push("type", "property");
					_tmp.push("name", $var.$0);
					_tmp.push("modifiers", $modifiers);
					$return.push(_tmp);
				}
			} else
				throw("not valid property");
			// for( auto  [$key_rtt, $var ]: $list_vars) {
			// // if (sizeof ( $vars ) != 1)
			// // throw  ( "not valid property declare1" );
			// $return [] = [ "type" => "property","name" => $var .$0,"modifiers" => $modifiers
			// ];
			// }
			return $return;
		}
	} catch (...) {
		return false;
	}
}
Mixed is_method_def(tokens_line $tokens_line1_arr) {
	arr_ls $modifiers;
	long $start_func_section;
	Mixed $return;
	token $token;
	tokens_line $func_section;
	$start_func_section = -1;
	for (auto [$i, $token] : $tokens_line1_arr) {
		if ($token.$1 == "modifier") {
			array_push($modifiers, $token.$0);
		} else {
			$start_func_section = $i;
			break;
		}
	}
	if ($start_func_section == -1)
		throw("non-function in method");
	$func_section = array_slice($tokens_line1_arr, $start_func_section);
	$return = is_function_def($func_section);
	if (!$return)
		return false;
	if (!$modifiers.empty())
		$return[2] = $modifiers;
	else
		$return[2] = { { 0, "public" } };
	return $return;
}
Mixed parse_class(tokens_line1_arr $class_def_block) {
	Mixed $return;
	unsigned long $i;
	tokens_line1 $line;
	Mixed $result;
	Mixed $property;
	Mixed $result1;
	$class_def_block = array_values($class_def_block);
	for ($i = 0; $i < sizeof($class_def_block); $i++) {
		$line = $class_def_block[$i];
		$result = parse_property($line.$0);
		if (!($result.valueArray.empty())) {
			for (auto [$key_rtt, $property] : $result.valueArray) {
				$return.push($property);
			}
		} else if ($result = is_method_def($line.$0)) {
			$result1 = process_function_def($i, $class_def_block, $result,
					true);
			$result1["type"] = "method";
			$result1["modifiers"] = $result[2];
			$return.push($result1);
		} else {
			throw("wrong class internal");
		}
	}
	$return.push("type", "block");
	$return.push("body", $return);
	return $return;
}
Mixed process_class_def(long $line_num, tokens_line1_arr $tokens_line1_arr,
		Mixed $class_name) {
	getline_subblock_t $getline_subblock;
	tokens_line1_arr $class_def_block;
	Mixed _tmp;
	$getline_subblock = getline_subblock($tokens_line1_arr, $line_num);
	$line_num += $getline_subblock.i;
	$class_def_block = $getline_subblock.arr;
	_tmp.push("type", "class_def");
	_tmp.push("name", $class_name["class"]);
	_tmp.push("extends", $class_name["extends"]);
	_tmp.push("body", parse_class($class_def_block));
	__classes.push(_tmp);
	return Mixed();
}
Mixed is_catch_line(long $line, tokens_line1_arr $tokens_line1_arr) {
	Mixed $return;
	tokens_line $line_tokens;
	string $_e;
	$line_tokens = remove_spaces_from_tokens_arr($tokens_line1_arr[$line].$0);
	if ($line_tokens[0].$0 == "catch" && $line_tokens[0].$1 == "keyword") {
		if (sizeof($line_tokens) == 1) {
			$return.push("catch");
			$return.push("^Exception");
			$return.push("$_e");
			return $return;
		} else if (sizeof($line_tokens) == 2 && $line_tokens[1].$1 == "class") {
			$return.push("catch");
			$return.push($line_tokens[1].$0);
			$return.push("$_e");
			return $return;
		} else if (sizeof($line_tokens) == 3 && $line_tokens[1].$1 == "class"
				&& $line_tokens[2].$1 == "var") {
			$return.push("catch");
			$return.push($line_tokens[1].$0);
			$return.push($line_tokens[2].$0);
			return $return;
		} else
			throw("invalid catch");
	}
	return false;
}
bool is_finally_line(long $line, tokens_line1_arr $tokens_line1_arr) {
	tokens_line $line_tokens;
	$line_tokens = remove_spaces_from_tokens_arr($tokens_line1_arr[$line].$0);
	if ($line_tokens[0].$0 == "finally" && $line_tokens[0].$1 == "keyword") {
		if (sizeof($line_tokens) == 1)
			return true;
		else
			throw("invalid finally");
	}
	return false;
}
Mixed process_try(long $line, tokens_line1_arr $tokens_line1_arr) {
	Mixed $return;
	long $tabs_lv;
	Mixed $blocks_type, _tmp, _tmp1;
	long $block_num;
	map<long, tokens_line1_arr> $blocks;
	long $i;
	Mixed $catch_line_parsed;
	tokens_line $catch_line;
	Mixed $catches;
	Mixed $try;
	long $try_count;
	Mixed $finally;
	long $finally_count;
	$tabs_lv = $tokens_line1_arr[$line].$1;
	_tmp.push("try");
	$blocks_type.push(_tmp);
	$block_num = 0;
	_tmp = Mixed();
	for ($i = $line + 1; $i < (long) sizeof($tokens_line1_arr); $i++) {
		if ($tokens_line1_arr[$i].$1 < $tabs_lv)
			break;
		if ($tokens_line1_arr[$i].$1 == $tabs_lv && ($catch_line_parsed =
				is_catch_line($i, $tokens_line1_arr))) {
// $catch_line = remove_all_spaces ( $tokens_arr [$i] .$0 );
			$block_num++;
			$blocks_type.push($catch_line_parsed);
		} else if ($tokens_line1_arr[$i].$1 == $tabs_lv
				&& is_finally_line($i, $tokens_line1_arr)) {
			$block_num++;
			$blocks[$block_num] = { };
			_tmp = Mixed();
			_tmp.push("finally");
			$blocks_type.push(_tmp);
		} else if ($tokens_line1_arr[$i].$1 == $tabs_lv) {
			break;
		} else if ($tokens_line1_arr[$i].$1 > $tabs_lv) {
			if (!isset($blocks, $block_num))
				$blocks[$block_num] = { };
			array_push($blocks[$block_num], $tokens_line1_arr[$i]);
		}
	}
	$line = $i - 1;
	$catches = Mixed();
	$try = Mixed();
	$try_count = 0;
	$finally = Mixed();
	$finally_count = 0;
	for ($i = 0; $i < (long) sizeof($blocks_type); $i++) {
		if ($blocks_type[$i][0] == "catch") {
			_tmp.push("exception_class", $blocks_type[$i][1]);
			_tmp.push("catch_var", $blocks_type[$i][2]);
			_tmp.push("body", structurelize($blocks[$i]));
			$catches.push(_tmp);
		} else if ($blocks_type[$i][0] == "try") {
			$try_count++;
			if ($try_count > 1)
				throw("multiple try blocks");
			$try = structurelize($blocks[$i]);
		} else if ($blocks_type[$i][0] == "finally") {
			$finally_count++;
			if ($finally_count > 1)
				throw("multiple try blocks");
			$finally = structurelize($blocks[$i]);
		}
	}
	if (sizeof($catches) < 1)
		throw("try but no catch");
	$return.push("type", "try");
	$return.push("body", $try);
	$return.push("catch", $catches);
	$return.push("finally", $finally);
	return $return;
}
Mixed process_defcat(long $line, tokens_line1_arr $tokens_line1_arr) {
	long $tabs_lv;
	tokens_line1_arr $defcat;
	tokens_line1_arr $deffin;
	bool $is_in_deffin;
	long $i;
	map<long, tokens_line1_arr> $defcat_blocks;
	map<long, Mixed> $defcat_blocks1;
	long $defcat_blocks_i;
	arr_ls $defcat_exception_classes;
	Mixed $defcat_rs, $return;
	Mixed $defcat_block;
	string $_e;
	$tabs_lv = $tokens_line1_arr[$line].$1;
	$is_in_deffin = false;
	for ($i = $line + 1; $i < (long) sizeof($tokens_line1_arr); $i++) {
		if ($tokens_line1_arr[$i].$1 < $tabs_lv) {
			break;
		} else if ($tokens_line1_arr[$i].$1 == $tabs_lv
				&& $tokens_line1_arr[$i].$0[0].$0 == "deffin") {
			$is_in_deffin = true;
		} else if ($tokens_line1_arr[$i].$1 == $tabs_lv
				&& $tokens_line1_arr[$i].$0[0].$0 != "deffin") {
			break;
		} else if ($tokens_line1_arr[$i].$1 > $tabs_lv) {
			if ($is_in_deffin)
				array_push($deffin, $tokens_line1_arr[$i]);
			else
				array_push($defcat, $tokens_line1_arr[$i]);
		}
	}
	if ($defcat.empty())
		return false;
	$line = $i;
	$defcat_blocks = { };
	$defcat_blocks_i = -1;
	$defcat_exception_classes = { };
	$defcat = rtrim_all_lines_arr($defcat);
	for ($i = 0; $i < (long) sizeof($defcat); $i++) {
		if ($defcat[$i].$1 == ($tabs_lv + 1))
			if (sizeof($defcat[0].$0) == 1 && $defcat[0].$0[0].$1 == "class") {
				array_push($defcat_exception_classes, $defcat[$i].$0[0].$0);
				$defcat_blocks_i++;
			} else
				throw("Invalid defcat exception class");
		else if ($defcat[$i].$1 > ($tabs_lv + 1)) {
			if (!isset($defcat_blocks, $defcat_blocks_i))
				$defcat_blocks[$defcat_blocks_i] = { };
			array_push($defcat_blocks[$defcat_blocks_i], $defcat[$i]);
		}
	}
	if (sizeof(array_unique($defcat_exception_classes))
			!= sizeof($defcat_exception_classes))
		throw("Non unique catch in defcat");
	$defcat_rs = Mixed();
	for (auto [$i, $defcat_block] : $defcat_blocks) {
		$defcat_blocks1[$i] = structurelize($defcat_block);
		$defcat_rs.push("exception_class", $defcat_exception_classes[$i]);
		$defcat_rs.push("catch_var", "$_e");
		$defcat_rs.push("body", $defcat_blocks1[$i]);
	}
	$return.push("type", "defcat");
	$return.push("body", $defcat_rs);
	$return.push("deffin", structurelize($deffin));
	return $return;
}
Mixed structurelize(tokens_line1_arr $tokens_line1_arr) {
	Mixed $return, _tmp, _tmp1;
	Mixed $defcat_rs;
	long $line;
	tokens_line1 $tokens_n_lv;
	tokens_line $tokens;
//	long $block_lv;
	Mixed $line_rs;
	Mixed $func_declare;
	Mixed $class_name;
// $tokens_arr = remove_blank_lines ( $tokens_arr );
	for ($line = 0; $line < (long) sizeof($tokens_line1_arr); $line++) {
		$tokens_n_lv = $tokens_line1_arr[$line];
		$tokens = ltrim_arr($tokens_n_lv.$0);
// $block_lv = $tokens_n_lv .$1;
		if ($tokens[0].$0 == "if" && $tokens[0].$1 == "keyword") {
			$line_rs = process_if($line, $tokens_line1_arr);
		} else if ($tokens[0].$0 == "for" && $tokens[0].$1 == "keyword") {
			$line_rs = process_for($line, $tokens_line1_arr);
		} else if ($tokens[0].$0 == "while" && $tokens[0].$1 == "keyword") {
			$line_rs = process_while($line, $tokens_line1_arr);
		} else if ($func_declare = is_function_def($tokens)) {
			$line_rs = process_function_def($line, $tokens_line1_arr,
					$func_declare);
		} else if ((bool) ($class_name = is_class_def($tokens))) {
			$line_rs = process_class_def($line, $tokens_line1_arr, $class_name);
		} else if ($tokens[0].$0 == "try" && $tokens[0].$1 == "keyword") {
			$line_rs = process_try($line, $tokens_line1_arr);
		} else if ($tokens[0].$0 == "defcat" && $tokens[0].$1 == "keyword") {
			$defcat_rs = process_defcat($line, $tokens_line1_arr);
			continue;
		} else
			$line_rs = parse_expression($tokens_n_lv.$0);
		$return.push($line_rs);
	}
	if ($defcat_rs) {
		_tmp1.push("type", "block");
		_tmp1.push("body", $return);
		_tmp.push("type", "try");
		_tmp.push("body", _tmp1);
		_tmp.push("catch", $defcat_rs["body"]);
		_tmp.push("finally", $defcat_rs["deffin"]);
		$return.push("type", "block");
		$return.push("body", _tmp);
		return $return;
	}
	$return.push("type", "block");
	$return.push("body", $return);
	return $return;
}
string process_string(string $str) {
	arr_ls $arr;
	arr_ls $return;
	long $k;
	string $v;
	$arr = str_split($str);
	$return = { };
	for ($k = 0; $k < (long) sizeof($arr); $k++) {
		$v = $arr[$k];
		if ($v == "\\" && isset($arr, $k + 1)) {
			array_push($return, $arr[$k + 1]);
			$k++;
		} else {
			array_push($return, $v);
		}
	}
	return implode((string) "", $return);
}
tokens_line1_arr merge_strings(tokens_line1_arr $tokens_line1_arr) {
	tokens_line1_arr $return;
//	long $k;
	tokens_line1 $tokens_line, _tmp;
	string $current_str;
//	long $k1;
	token $token;
	$return = { };
	for (auto [$k, $tokens_line] : $tokens_line1_arr) {
		_tmp.$0 = { };
		_tmp.$1 = $tokens_line1_arr[$k].$1;
		$return[$k] = _tmp;
		$current_str = "";
		for (auto [$k1, $token] : $tokens_line.$0) {
			if ($token.$1 == "string") {
				$current_str += $token.$0;
				continue;
			} else if ($token.$1 == "spaces") {
				if (!$current_str.empty()) {
					$current_str += $token.$0;
					continue;
				} else {
					array_push($return[$k].$0, $token);
				}
			} else {
				if (!$current_str.empty()) {
					array_push($return[$k].$0,
							token(trim($current_str), "string"));
					if ($tokens_line.$0[$k1 - 1].$1 == "spaces")
						array_push($return[$k].$0, $tokens_line.$0[$k1 - 1]);
				}
				$current_str = "";
				array_push($return[$k].$0, $token);
			}
		}
		if (!$current_str.empty()) {
			array_push($return[$k].$0, token(trim($current_str), "string"));
			if ($tokens_line.$0[sizeof($tokens_line.$0) - 1].$1 == "spaces")
				array_push($return[$k].$0,
						$tokens_line.$0[sizeof($tokens_line.$0) - 1]);
		}
	}
	for (auto [$k, $tokens_line] : $return) {
		for (auto [$k1, $token] : $tokens_line.$0) {
			if ($token.$1 == "string")
				$return[$k].$0[$k1].$0 = process_string($return[$k].$0[$k1].$0);
		}
	}
	return $return;
}
Mixed array_merge_unique(Mixed &$arr, Mixed $arr1) {
	Mixed $ele1, _tmp, $return;
	for (auto [$key_rtt, $ele1] : $arr1.valueArray) {
		if (!in_array($ele1, $arr))
			$arr.push($ele1);
	}
	return $arr;
}
Mixed find_all_unique_types_non_block_in_body(string $type, Mixed $input) {
	Mixed $return;
	Mixed $clause;
	if (!$input.contains("body")) {
		if (isset($input, "name") && $input["type"] == $type) {
			$return.push($input);
			return $return;
		} else
			return Mixed();
	} else {
		$return = Mixed();
		for (auto [$key_rtt, $clause] : $input["body"].valueArray) {
			array_merge_unique($return,
					find_all_unique_types_non_block_in_body($type, $clause));
		}
		return $return;
	}
}
bool find_an_obj_in_body(Mixed $obj, Mixed $input) {
	Mixed $clause;
	if ($input.contains("name") && $input.contains("type")
			&& $input["name"] == $obj["name"]
			&& $input["type"] == $obj["type"]) {
		return true;
	} else if ($input.contains("body")) {
		for (auto [$key_rtt, $clause] : $input["body"].valueArray) {
			if (find_an_obj_in_body($obj, $clause))
				return true;
		}
		return false;
	}
	return false;
}
string array_remove_each(Mixed &$arr, Mixed $arr1) {
//	long $k;
	Mixed $ele;
	Mixed $ele1;
	for (auto [$k, $ele] : $arr.valueArray) {
		for (auto [$key_rtt, $ele1] : $arr1.valueArray) {
			if ($ele == $ele1)
				$arr.del($k);
		}
		$arr = array_values($arr);
	}
	return $arr;
}
Mixed find_all_vars_in_function_def(Mixed $function) {
	Mixed $inner_vars;
	$inner_vars = find_all_unique_types_non_block_in_body("var",
			$function["body"]);
	array_remove_each($inner_vars, $function["vars"]);
	return $inner_vars;
}
bool find_return_in_body(Mixed $body) {
	Mixed _tmp1;
	_tmp1.push("name", "@return");
	_tmp1.push("type", "function");
	return find_an_obj_in_body(_tmp1, $body);
}
void parse(string $path) {
	string $content;
	tokens_line1_arr $tokens_line1_arr;
	Mixed $structure_arr;
	$content = file_get_contents($path);
	$tokens_line1_arr = tokenize($content);
	$tokens_line1_arr = merge_strings($tokens_line1_arr);
	$structure_arr = structurelize($tokens_line1_arr);
	__main = $structure_arr;
}

//==================================================================================================================================================================
Mixed __answer_var, __all_global_vars, __all_local_vars;
void assign_var(string var, Mixed value) {
//TODO:
	;
}
//Mixed eval(Mixed _expr);
//long exec(Mixed _parsed) {
//	Mixed _v;
//	if (_parsed.type != "block") {
//		throw "not a block";
//	}
//	for (auto [_k, _v] : _parsed.valueArray) {
//		if ((*_v)["type"] == "ifs") {
//			for (auto [_k1, _v1] : (*_v)["ifs"].valueArray) {
//				bool _check = (bool) eval((Mixed) (*_v1)["condition"]);
//				if (_check) {
//					exec((Mixed) (*_v1)["body"]);
//					break;
//				}
//			}
//			exec((Mixed) (*_v)["else"]);
//		} else if ((*_v)["type"] == "try") {
//			try {
//				exec((Mixed) (*_v)["try"]);
//			} catch (GtlangException &$e) {
//				for (auto [_k1, _v1] : (*_v)["catches"].valueArray) {
//					if ($e.msg == (string) _v1["exception_class"]) {
//						assign_var((string) _v1["catch_var"], Mixed($e.msg));
//						exec(_v1["body"]);
//					}
//				}
//			}
//		} else if ((*_v)["type"] == "for") {
//			;
//		} else if ((*_v)["type"] == "while") {
//			;
//		} else if ((*_v)["type"] == "foreach") {
//			;
//		} else if ((*_v)["type"] == "func_def") {
//			;
//		} else if ((*_v)["type"] == "class_def") {
//			;
//		} else if ((*_v)["type"] == "method") {
//			;
//		} else {
//			eval(_v);
//		}
//	}
//}
//Mixed eval(Mixed _expr) {
//	Mixed _return;
//	return _return;
//}
Mixed _global_vars, _local_vars;
long _current_func_lv = 0;
long _break, _continue = 0;
Mixed gt_eval (Mixed $parsed){
	Mixed $find_result;
	Mixed $result;
	Mixed $backup_vars;
	if (!is_array($parsed))
		return $parsed;
	if (in_array ( $parsed ["type"], [ "number","string"
			] ))
		return $parsed["name"];
	if ($parsed["type"] == "expr") {
		if (sizeof($parsed["body"]) == 1) {
			return gt_eval($parsed["body"].$0);
		} else {
			$find_result = find_operator_in_expr($parsed);
			$result = gt_do($find_result["operator"], $find_result["expr"],
					$find_result["opt_pos"]);
			return $result;
		}
	}
	if ($parsed["type"] == "array") {
		return create_array_var($parsed);
	}
	if ($parsed["type"] == "var") {
		return get_value($parsed);
	}
	if ($parsed["type"] == "var_global") {
		return get_var_global_value($parsed);
	}
	if ($parsed["type"] == "function") {
		$backup_vars = $local_vars;
		// $current_func_lv ++;
		$result = call_function($parsed);
		$local_vars = $backup_vars;
		// $current_func_lv --;
		return $result;
	}
	if ($parsed["type"] == "array") {
		return create_array_var($parsed);
	}
	if ($parsed["type"] == "assignment") {
		assign_var($parsed["left"], $result = gt_eval($parsed["right"]));
		return $result;
	}
	if ($parsed["type"] == "complex_value") {
		$result = get_value($parsed);
		return $result;
	}
	throw("unsupported expr");
}

Mixed* get_ref_of_element(Mixed $value_name, Mixed $value_key) {
	Mixed $name;
	Mixed $key;
	Mixed $ref;
	Mixed $return;
	if ($value_name["type"] == "expr") {
		return get_ref_of_element($value_name["body"], $value_key);
	} else if ($value_name["type"] == "var") {
		$name = &get_ref_single($value_name, Mixed());
		$key = gt_eval($value_key);
		return $name[$key];
	} else if ($value_name["type"] == "complex_value") {

		$ref = &get_ref_of_element($value_name["name"], $value_name["key"]);

		$key = gt_eval($value_key);
		if (isset($ref[$key])) {
			$return = &$ref[$key];
		} else {
			$ref[$key] = null;
			$return = &$ref[$key];
		}
		return $return;
	} else {
		throw("not valid left side of assignment");
	}
}
Mixed assign_var(Mixed $var, Mixed $value) {
	Mixed $var_name;
	Mixed $return;
	Mixed *$ref;
	if ($var["type"] == "var") {
		$var_name = $var["name"];
		if (_current_func_lv == 0) {
			$return = _global_vars[$var_name] = ($value);
			return $return;
		} else {
			$return = _local_vars[$var_name] = ($value);
			return $return;
		}
	} else if ($var["type"] == "var_global") {
		$var_name = $var["name"];
		if (isset(_global_vars, (string) $var_name)) {
			$return = _global_vars[$var_name] = ($value);
			return $return;
		} else
			throw("no global var $var_name");
	} else if ($var["type"] == "complex_value") {
		$ref = get_ref_of_element($var["name"], gt_eval($var["key"]));
		$ref = $value;
	} else
		throw("not valid left side of assignment");
}
function& get_ref_single($value_name, $default_value_if_var_not_exist = null) {
	if ($value_name["type"] == "var") {
		$var_name = $value_name["name"];
		if ($GLOBALS["current_func_lv"] == 0) {
			if (!isset($GLOBALS["global_vars"][$var_name]))
				$GLOBALS["global_vars"][$var_name] =
						$default_value_if_var_not_exist;
			return $GLOBALS["global_vars"][$var_name];
		} else {
			if (!isset($GLOBALS["local_vars"][$var_name]))
				$GLOBALS["local_vars"][$var_name] =
						$default_value_if_var_not_exist;
			return $GLOBALS["local_vars"][$var_name];
		}
	} else {
		throw("expr not allowed here");
	}
}
Mixed get_value(Mixed $value) {
	Mixed $var_name;
	Mixed $return;
	Mixed $result;
	if ($value["type"] == "var") {
		$var_name = $value["name"];
		if (_current_func_lv == 0) {
			$return = _global_vars[$var_name];
			return $return;
		} else {
			$return = _local_vars[$var_name];
			return $return;
		}
	} else if ($value["type"] == "complex_value") {
		$result = gt_eval($value["name"]);
		return $result[gt_eval($value["key"])];
	}
}
function& ref_var($var_complex) {
	if ($var_complex["type"] == "var") {
		$var_name = $var_complex["name"];
		if ($GLOBALS["current_func_lv"] == 0) {
			$return = &$GLOBALS["global_vars"][$var_name];
			return $return;
		} else {
			$return = &$GLOBALS["local_vars"][$var_name];
			return $return;
		}
	}
}
void gt_exec(Mixed $parsed) {
	Mixed $cmd;
	Mixed $if;
	Mixed $is_catched;
	Mixed $;
	Mixed $e
	-;
	Mixed $answer_var;
	if ($parsed["type"] == "block" || $parsed["type"] == "inline_block") {
		for( auto const& [$key_rtt, $cmd ]: $parsed ["body) {
				if ($break > 0 || $break > 0) {
					// $break --;
					return 1;
				}
				if ($cmd["type"] == "block" || $cmd["type"] == "inline_block") {
					gt_exec($cmd);
					continue;
				} else if ($cmd["type"] == "ifs") {
				for( auto const& [$key_rtt, $if ]: $cmd ["ifs) {
						if (gt_eval ( $if ["condition"] )) {
							gt_exec ( $if ["body"] );
							break;
						}
					}
					gt_exec($cmd["else"]);
				} else if ($cmd["type"] == "for") {
					gt_eval($cmd["init"]);
					while (true) {
						if ($break) {
							$break = 0;
							break;
						}
						if ($continue > 1) {
							$continue--;
							break;
						}
						if ($continue == 1) {
							$break--;
							continue;
						}
						gt_eval($cmd["increment"]);
						gt_exec($cmd["body"]);
						if (!gt_eval($cmd["terminate"]))
							break;
					}
				} else if ($cmd["type"] == "while") {
					while (true) {
						if (!gt_eval($cmd["condition"]))
							break;
						if ($break > 0) {
							$break--;
							break;
						}
						if ($continue > 1) {
							$continue--;
							break;
						}
						if ($continue == 1) {
							$break--;
							continue;
						}
						gt_exec($cmd["body"]);
					}
				} else if ($cmd["type"] == "try") {
					try {
						gt_exec($cmd["body"]);
					} catch (GTException $e) {
						$is_catched = false;
					for( auto const& [$key_rtt, $ catch ]: $cmd ["catch) {
							if (strpos ( $e->getMessage (), $ catch ["exception_class"] + ":" ) == 0) {
								assign_var ( $ catch ["catch_var"], $e );
								gt_exec ( $ catch ["body"] );
								$is_catched = true;
								break;
							}
						}
						if (!$is_catched)
							throw("not catched");
					}
				}
				else if (isset ( $cmd ["body"] ) && $cmd ["body"] .$0 == [ "name" => "break","type" => "keyword"
						]) {
					if (sizeof ( $cmd ["body"] ) == 1) {
						$break = 1;
						return 0;
					} else if (sizeof ( $cmd ["body"] ) == 2 && $cmd ["body"] .$1 ["type"] == "number") {
						$break = $cmd ["body"] .$1 ["name"];
						return 0;
					} else
					throw ( "incorrect break" );
				} else if (isset ( $cmd ["body"] ) && $cmd ["body"] .$0 == [ "name" => "continue","type" => "keyword"
						]) {
					if (sizeof ( $cmd ["body"] ) == 1) {
						$continue = 1;
						return 0;
					} else if (sizeof ( $cmd ["body"] ) == 2 && $cmd ["body"] .$1 ["type"] == "number") {
						$break = $cmd ["body"] .$1 ["name"];
						return 0;
					} else
					throw ( "incorrect break" );
				} else {
					assign_var ( [ "name" => "\$answer_var","type" => "var"
							], gt_eval ( $cmd ) );
				}
			}
		}
	}
	Mixed find_operator_in_expr(Mixed $expr) {
		long $k;
		Mixed $obj;
	for( auto const& [$k, $obj]: $expr ["body) {
			if ($obj ["type"] == "operator") {
				$expr ["body"] .erase($k);
				return [ "operator" => $obj ["name"],"expr" => array_values ( $expr ["body"] ),"opt_pos" => $k
				];
			}
		}
		return Mixed();
	}
	Mixed gt_do(string $opt, token $params, long $opt_pos) {
		Mixed $return1;
		Mixed $return0;
		Mixed $return;
		if ($opt == "+") {
			return gt_eval($params.$0) + gt_eval($params.$1);
		} else if ($opt == "-") {
			return gt_eval($params.$0) - gt_eval($params.$1);
		} else if ($opt == "*") {
			return gt_eval($params.$0) * gt_eval($params.$1);
		} else if ($opt == "/") {
			return gt_eval($params.$0) / gt_eval($params.$1);
		} else if ($opt == "%") {
			return gt_eval($params.$0) % gt_eval($params.$1);
		} else if ($opt == "**") {
			return gt_eval($params.$0) * *gt_eval($params.$1);
		} else if ($opt == "&&") {
			return gt_eval($params.$0) && gt_eval($params.$1);
		} else if ($opt == "||") {
			return gt_eval($params.$0) || gt_eval($params.$1);
		} else if ($opt == "!") {
			return !gt_eval($params.$0);
		} else if ($opt == "==") {
			return gt_eval($params.$0) == gt_eval($params.$1);
		} else if ($opt == "==") {
			return gt_eval($params.$0) == gt_eval($params.$1);
		} else if ($opt == "<") {
			return gt_eval($params.$0) < gt_eval($params.$1);
		} else if ($opt == "<=") {
			return gt_eval($params.$0) <= gt_eval($params.$1);
		} else if ($opt == ">") {
			return gt_eval($params.$0) > gt_eval($params.$1);
		} else if ($opt == ">=") {
			return gt_eval($params.$0) >= gt_eval($params.$1);
		} else if ($opt == "!=") {
			return gt_eval($params.$0) != gt_eval($params.$1);
		} else if ($opt == "++") {
			assign_var($params.$0,
					$return1 = ($return0 = gt_eval($params.$0)) + 1);
			if ($opt_pos == 0)
				return $return0;
			else
				return $return1;
		} else if ($opt == "--") {
			assign_var($params.$0["name"],
					$return1 = ($return0 = gt_eval($params.$0)) - 1);
			if ($opt_pos == 0)
				return $return0;
			else
				return $return1;
		} else if ($opt == "+:") {
			assign_var($params.$0["name"],
					$return = gt_eval($params.$0) + gt_eval($params.$1));
			return $return;
		} else if ($opt == "-:") {
			assign_var($params.$0["name"],
					$return = gt_eval($params.$0) - gt_eval($params.$1));
			return $return;
		} else if ($opt == "*:") {
			assign_var($params.$0["name"],
					$return = gt_eval($params.$0) * gt_eval($params.$1));
			return $return;
		} else if ($opt == "/:") {
			assign_var($params.$0["name"],
					$return = gt_eval($params.$0) / gt_eval($params.$1));
			return $return;
		} else if ($opt == "%:") {
			assign_var($params.$0["name"],
					$return = gt_eval($params.$0) % gt_eval($params.$1));
			return $return;
		} else {
			throw("unknown operator");
		}
	}
	Mixed get_var_global_value(Mixed $parsed) {
		return _global_vars[$parsed["name"]];
	}
	Mixed get_var_local_value(Mixed $parsed) {
		return _local_vars[$parsed["name"]];
	}
	Mixed replace_get_ele_with_complex_value(Mixed $expr) {
		long $k;
		Mixed $v;
		if (!is_array($expr))
			return $expr;
		if (isset ( $expr ["body"] .$1 ) && $expr ["body"] .$1 == [ "name" => "get_ele","type" => "operator"
		] && sizeof ( $expr ["body"] ) == 3) {
		$expr = [ "type" => "complex_value","name" => $expr ["body"] .$0,"key" => $expr ["body"] .$2
		];
	}
	// if (isset ( $expr ["body"] ))
	for (auto const& [$k, $v] : $expr) {
		$expr[$k] = replace_get_ele_with_complex_value($v);
	}
	return $expr;
}
Mixed call_function(Mixed $parsed) {
	Mixed $function;
	Mixed $defined_func;
	arr_ls $params_str_arr;
	Mixed $tmp;
	Mixed $i;
	Mixed $arg;
	string $params_str;
	Mixed $result;
	long $count_required_params;
	Mixed $var;
	long $k;
	long $j;
	Mixed $passed_vars_value;
	Mixed $passed_value;
	// count required params;
	$function = Mixed();
	for (auto const& [$key_rtt, $defined_func] : $funcs) {
		if ($defined_func["name"] == $parsed["name"]) {
			$function = $defined_func;
			break;
		}
	}
	if (!$function) {
		try {
			$params_str_arr = $tmp = Mixed();
			for( auto const& [$i, $arg]: $parsed ["args) {
					$tmp [] = gt_eval ( $arg );
					$params_str_arr [] = "\$tmp[$i]";
				}
				$params_str = implode(",", $params_str_arr);
				if ($parsed["name"] == "@echo") {
					eval(
							php_translate($parsed["name"]) + "(" + $params_str
									+ ");");
					return 0;
				} else {
					eval(
							'$result = ' + php_translate($parsed["name"]) + "("
									+ $params_str + ");");
					return $result;
				}
			}
		catch (Exception $e) {
			throw ("function not defined");
		}
	}
	if (sizeof($parsed["args"]) < $function["vars"]) {
		throw ("function call dont more params than function define");
	}
	$count_required_params = 0;
	for( auto const& [$key_rtt, $var ]: $function ["vars) {
			if (isset ( $var .$1 ))
			break;
			$count_required_params ++;
		}
		if (sizeof($parsed["args"]) < $count_required_params)
		throw ("function call dont have enough params");
		// assign called params
		for( auto const& [$k, $arg]: $parsed ["args) {
				$var = $function ["vars"] [$k];
				assign_var ( $var, gt_eval ( $arg ) );
			}
			// assign default un-called params
			if ($k < sizeof($function["vars"])) {
				for ($j = $k; $j < sizeof($function["vars"]); $j++) {
					$passed_vars_value [] = $function ["vars"] [$j] .$1;
				}
			}
			_current_func_lv++;
			for( auto const& [$j, $passed_value]: $passed_vars_value) {
				assign_var ( $function ["vars"] [$j] .$0, $passed_value );
			}
			gt_exec ($function["body"]);
			_current_func_lv--;
		}
		function create_array_var($parsed) {
			$return = Mixed();
			foreach ( $parsed ["body"] as $element ) {
				$return [gt_eval ( $element ["key"] )] = gt_eval ( $element ["value"] );
			}
			return $return;
		}
		f
