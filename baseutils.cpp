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

#include<algorithm>
#include"baseutils.h"

vector<int> toDigits(int n, int base)
{
    vector<int> out;
    if (n)
    {
        while (n)
        {
            out.push_back(n % base);
            n /= base;
        }
    }
    else
    {
        out.push_back(0);
    }
    reverse(out.begin(), out.end());
    return out;
}
int fromDigits(vector<int> digits, int base)
{
    int n = 0;
    int b = 1;
    for (int i = (int)digits.size() - 1; i >= 0; i--)
    {
        n += digits[i] * b;
        b *= base;
    }
    return n;
}
vector<int> convertBase(vector<int> digits, int b, int c)
{
    return toDigits(fromDigits(digits, b), c);
}
vector<int> alpha_to_binary_int(const char &c)
{
    vector<int> binary = toDigits((int)c, 2);
    return binary;
}
vector<vector<int>> alpha_to_binary_int2(const char &c)
{
    vector<vector<int>> out;
    vector<int> binary_half1 = toDigits((int)c >> 4, 2);
    vector<int> binary_half2 = toDigits((int)c & 0xF, 2);
    out.push_back(binary_half1);
    out.push_back(binary_half2);
    return out;
}
vector<vector<int>> string_to_binary_int2(const string &s)
{
    vector<vector<int>> out;
    for (int i = 0; i < s.size(); i++)
    {
        vector<int> binary_half1 = toDigits((int)s[i] >> 4, 2);
        vector<int> binary_half2 = toDigits((int)s[i] & 0xF, 2);
        out.push_back(binary_half1);
        out.push_back(binary_half2);
    }
    return out;
}
