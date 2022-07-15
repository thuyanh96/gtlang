#ifndef LIB_MIXED_H_
#define LIB_MIXED_H_

using namespace std;

bool isInt(double num) {
	return (ceilf(num) == num);
}
class GtlangException {
public:
	string msg;
	GtlangException(string str) {
		msg = str;
	}
};
class Mixed {
public:
	string type = "a";
	string valueStr = "";
	double valueNum = 0.0;
	bool valueBool = false;
	long index = 0;
	unordered_map<string, Mixed*> valueArray;

	Mixed() {
		this->type = "a";
		string valueStr = "";
		valueNum = 0.0;
		valueBool = false;
		index = 0;
		valueArray = { };
	}
	Mixed(const string value) {
		this->valueStr = value;
		this->type = "s";
	}
	Mixed(const char *value) {
		this->valueStr = value;
		this->type = "s";
	}
	Mixed(const long value) {
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const int value) {
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const double value) {
		this->valueNum = (double) value;
		this->type = "n";
	}
	Mixed(const bool value) {
		this->valueBool = value;
		this->type = "b";
	}
//	template<typename K, typename V>
	Mixed(token value) {
		Mixed newMixed = new Mixed(value.$0);
		Mixed newMixed1 = new Mixed(value.$1);
		this->valueArray["0"] = &newMixed;
		this->valueArray["1"] = &newMixed1;
		this->type = "a";
	}

	Mixed(tokens_line input) {
		Mixed newMixed;
		token _tk;
		for (auto [_k, _v] : input) {
			_tk = (token) _v;
			newMixed = new Mixed(_tk);
			this->valueArray[to_string(_k)] = &newMixed;
		}
		this->type = "a";
	}
	long getInt() {
		return (long) this->valueNum;
	}
	long getLen() {
		return this->valueArray.size();
	}
	Mixed(const arr_ls value) {
		for (auto [_k, _v] : value) {
			this->valueArray[to_string(_k)] = new Mixed((string) _v);
		}
	}
	Mixed(const tokens_line1 value) {
		this->valueArray["0"] = new Mixed(value.$0);
		this->valueArray["1"] = new Mixed(value.$1);
		this->type = "a";
	}
	Mixed(const tokens_line1_arr value) {
		for (auto [_k, _v] : value) {
			this->valueArray[to_string(_k)] = new Mixed((tokens_line1) _v);
		}
		this->type = "a";
	}
//	Mixed(const Mixed &value) {
//		this = value;
//	}
	void setStr(const string value) {
		this->valueStr = value;
		this->type = "s";
	}

	void setNum(const long value) {
		this->valueStr = value;
		this->type = "n";
	}

	void setNum(const double value) {
		this->valueStr = value;
		this->type = "n";
	}

	void setBool(bool value) {
		this->valueBool = value;
		this->type = "b";
	}

	void setArray(unordered_map<string, Mixed*> value) {
		this->valueArray = value;
		this->type = "a";
	}

	string getType() {
		return this->type;
	}
	template<typename K, typename V>
	void push(K key, V element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	void push(const Mixed element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	void push(const string element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	void push(const char *element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	void push(const double element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	void push(const bool element) {
		if (this->type != "a")
			throw "not an array to push";
		Mixed *elementPointer = new Mixed(element);
		this->valueArray[to_string(this->index)] = elementPointer;
		this->index++;
	}
	Mixed operator=(Mixed mixed1) {
		Mixed _tmp;
		if (mixed1.type != "a") {
			type = mixed1.type;
			string valueStr = mixed1.valueStr;
			valueNum = mixed1.valueNum;
			valueBool = mixed1.valueBool;
			index = mixed1.index;
			valueArray = { };
			return *this;
		} else {
			type = mixed1.type;
			string valueStr = mixed1.valueStr;
			valueNum = mixed1.valueNum;
			valueBool = mixed1.valueBool;
			index = mixed1.index;
			valueArray = { };
			for (auto& [_k, _v] : mixed1.valueArray) {
				_tmp = new Mixed();
				_tmp = *_v;
				valueArray[(string) _k] = _v;
			}
			return *this;
		}
	}
	Mixed operator=(int number) {
		this->valueNum = (double) number;
		this->type = "n";
		this->valueStr = "";
		this->valueBool = false;
		unset_r();
		return this;
	}
	Mixed operator=(float number) {
		this->valueNum = (double) number;
		this->type = "n";
		this->valueStr = "";
		this->valueBool = false;
		unset_r();
		return this;
	}
	Mixed operator=(const char *str) {
		this->valueNum = 0;
		this->type = "s";
		this->valueStr = str;
		this->valueBool = false;
		unset_r();
		return *this;
	}
	Mixed operator=(string str) {
		this->valueNum = 0;
		this->type = "s";
		this->valueStr = str;
		this->valueBool = false;
		unset_r();
		return *this;
	}
	Mixed operator=(bool tf) {
		this->valueNum = 0;
		this->type = "b";
		this->valueStr = "";
		this->valueBool = tf;
		unset_r();
		return *this;
	}
	template<typename V>
	Mixed operator=(map<long, V> _arr) {
		//		Mixed _return;
		try {
			unset_r();
			this->type = "a";
			string valueStr = "";
			valueNum = 0.0;
			valueBool = false;
			index = 0;
			for (auto [_k, _v] : _arr) {
				valueArray[to_string((long) _k)] = new Mixed((V) _v);
			}
			return *this;
		} catch (...) {
			throw "error convert to Mixed";
		}
	}
//	template<typename V>
//	void push(map<long, V> _arr) {
//		this->valueArray[to_string()];
//	}
//	Mixed(const token value) {
//		this->type = "a";
//		this->valueArray.insert( { "0", new Mixed(value.$0) });
//		this->valueArray.insert( { "1", new Mixed(value.$1) });
//	}
	Mixed& operator[](string key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = valueArray[key];
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	Mixed& operator[](const char *key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = valueArray[key];
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	Mixed& operator[](int key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = valueArray[to_string(key)];
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	Mixed& operator[](long key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = valueArray[to_string(key)];
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	Mixed& operator[](float key) {
		Mixed *_return = new Mixed();
		if (this->type != "a")
			throw "Getting element of non-array object";
		try {
			_return = valueArray[to_string(key)];
		} catch (...) {
			throw "Element not exist";
		}
		return *_return;
	}
	void unset_r() {
		unordered_map<string, Mixed*>::iterator it;
		for (it = this->valueArray.begin(); it != this->valueArray.end();
				it++) {
			if ((it->second)->type == "a")
				(*(it->second)).unset_r();
			else
				delete it->second;
		}
		this->valueArray.clear();
	}

//	void operator=(Mixed &arr) {
//		this->valueNum = 0;
//		this->type = "a";
//		this->valueStr = "";
//		this->valueBool = false;
//		unset_r();
//		this->valueArray = arr.valueArray;
//	}
	template<typename V>
	bool operator==(V v) {
		Mixed s = Mixed(v);
		if (*this == s)
			return true;
		else
			return false;
	}
	bool contains(string _key) {
		if (this->type == "a" && isset(this->valueArray, _key))
			return true;
		return false;
	}
	operator int() {
		if (this->type == "n")
			return (int) this->valueNum;
		if (this->type == "s") {
			try {
				return stoi(this->valueStr);
				return (int) stof(this->valueStr);
			} catch (...) {
				if (this->valueStr.size() > 0)
					return 1;
				return 0;
			}
		}
		if (this->type == "b") {
			if (this->valueBool)
				return 1;
			else
				return 0;
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return 1;
			else if (this->valueStr.size() > 0)
				return 1;
			return 0;
		}
		return 0;
	}
	operator float() {
		if (this->type == "n")
			return (float) this->valueNum;
		if (this->type == "s") {
			try {
//				return stoi(this->valueStr);
				return (float) stof(this->valueStr);
			} catch (...) {
				if (this->valueStr.size() > 0)
					return 1;
				return 0;
			}
		}
		if (this->type == "b") {
			if (this->valueBool)
				return 1;
			else
				return 0;
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return 1;
			else
				return 0;
		}
		return 0;
	}
	operator string() {
		if (this->type == "n")
			return to_string(this->valueNum);
		if (this->type == "s") {
			return this->valueStr;
		}
		if (this->type == "b") {
			if (this->valueBool)
				return "true";
			else
				return "";
		}
		if (this->type == "a") {
			if (this->valueArray.size() > 0)
				return "array";
			else
				return "";
		}
		return "";
	}
	operator bool() {
		return true;
	}
	operator token() {
		token _return;
		try {
			_return.$0 = (string) * (this->valueArray)["0"];
			_return.$1 = (string) * (this->valueArray)["1"];
			return _return;
		} catch (...) {
			return token();
		}
		return token();
	}
	tokens_line to_tokens_line() {
		tokens_line _return;
		try {
			for (auto [_k, _v] : this->valueArray) {
				_return[stol((string) _k)] = token(_v[0], _v[1]);
			}
			return _return;
		} catch (...) {
			throw "cannot convert to ls";
		}
		return {};
	}
	arr_ls to_ls() {
		arr_ls _return;
		try {
			for (auto [_k, _v] : this->valueArray) {
				_return[stol((string) _k)] = (string) (Mixed) _v;
			}
			return _return;
		} catch (...) {
			throw "cannot convert to ls";
		}
		return {};
	}
	void del(string _k) {
		this->valueArray.at(_k)->unset_r();
		this->valueArray.erase(_k);
	}
	Mixed& get_ref(string key) {
		if (this->type != "a")
			throw "not an array to get ref";
		return *(this->valueArray[key]);
	}
	bool operator==(string _compare) {
		return (this->valueStr == _compare);
	}
};

bool is_token(Mixed _arr) {
	if (_arr.valueArray.size() != 2)
		return false;
	if (!isset(_arr.valueArray, (string) "0"))
		return false;
	if (!isset(_arr.valueArray, (string) "1"))
		return false;
	if ((_arr.valueArray["0"])->type != "s")
		return false;
	if ((_arr.valueArray["1"])->type != "s")
		return false;
	return true;
}
bool isset(Mixed _arr, string _k) {
	if (_arr.valueArray.find(_k) == _arr.valueArray.end())
		return false;
	return true;
}
bool isset(Mixed _arr, long _kl) {
	string _k = to_string(_kl);
	if (_arr.valueArray.find(_k) == _arr.valueArray.end())
		return false;
	return true;
}
//token reset(Mixed _arr) {
//	return (token) *(_arr.valueArray.begin()->second);
//}
void array_shift_nr(Mixed &_arr) {
	_arr.valueArray.erase(_arr.valueArray.begin());
}
void array_pop_nr(Mixed &_arr) {
	_arr.valueArray.erase(prev(_arr.valueArray.end()));
}

Mixed array_slicem(Mixed _arr, long _pos, long _pos1 = -1) {
	Mixed _return;
	return Mixed();
}
Mixed reset(Mixed tokens_arr) {
	return Mixed();
}
struct mixed_to_tokens_line_with_place_holders_rs {
public:
	tokens_line $0;
	map<string, Mixed> $1;
	mixed_to_tokens_line_with_place_holders_rs() {
		;
	}
	mixed_to_tokens_line_with_place_holders_rs(tokens_line _tl,
			map<string, Mixed> _map_placeholders) {
		$0 = _tl;
		$1 = _map_placeholders;
	}
}
;
mixed_to_tokens_line_with_place_holders_rs mixed_to_tokens_line_with_place_holders(
		Mixed $complex_expr_arr) {
	tokens_line _return;
	token _tmp;
	map<string, Mixed> _map_placeholders;
	long i = 0;
	for (const auto& [$k, $item] : $complex_expr_arr.valueArray) {
		if (is_token((Mixed) $item)) {
			_tmp = token((string) $item[0], (string) $item[1]);
			array_push(_return, _tmp);
		} else {
			array_push(_return, token(to_string(i), "placeholder"));
			_map_placeholders.insert( { $k, $item });
		}
		i++;
	}
	return mixed_to_tokens_line_with_place_holders_rs(_return,
			_map_placeholders);
}
bool in_array(Mixed _find, Mixed _arr) {
	for (const auto& [_i, _v] : _arr.valueArray) {
		if ((Mixed) _v == _find)
			return true;
	}
	return false;
}
Mixed array_values(Mixed _arr) {
	Mixed _return;
	return _return;
}
Mixed replace_placeholders_recruisively(Mixed _arr,
		map<string, Mixed> _map_placeholders) {
	for (const auto& [_k, _v] : _arr.valueArray) {
		if (is_token((Mixed) _v) && _v[1] == "placeholder") {
			_arr[_k] = _v[0];
		} else if (((Mixed) _v).type == "a") {
			_arr[_k] = replace_placeholders_recruisively((Mixed) _v,
					_map_placeholders);
		}
	}
	return _arr;
}
#endif //LIB_MIXED_H_

