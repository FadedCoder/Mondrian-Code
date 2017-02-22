/* Copyright 2017 Alexandru Bratosin,
 *                Sergey Popov,
 *                Sampriti Panda,
 *                Urtkash Dixit
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>
using namespace std;

vector<int> toDigits(int n, int base); /// This method returns a vector<int> with the digits of the given int n in a specified base
int fromDigits(vector<int> digits, int base); /// This method receives the digits of a number and reassembles them to return the original value as an int with a specified base
vector<int> convertBase(vector<int> digits, int b, int c); /// This method converts a number from base b to base c. The number is given as a vector of digits.
vector <int> alpha_to_binary_int(const char &c); /// This method returns an 8-length vector whose elements represent the bits of a char
vector <vector<int>> alpha_to_binary_int2(const char &c); /// This method returns two 4-length vectors whose elements represent the bits of a char
vector<vector<int>> string_to_binary_int2(const string &s);