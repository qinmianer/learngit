#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
       if (needle.length() > haystack.length()) return -1;
        int len_h = haystack.length(), len_n = needle.length();
        for(int i = 0; i+len_n<=len_h; i++)
            if(haystack.substr(i, len_n) == needle)
                return i;
        return -1;
    }

    int divide(int dividend, int divisor) {
        if(dividend == INT_MIN && divisor == -1) return INT_MAX;  //溢出
        if(dividend == 0) return 0; // 0/any
        if(divisor == 1) return dividend;   // any/1
        if(divisor == -1) return 0-dividend; // any/-1

        if(divisor == INT_MIN) // any/INT_MIN
        {
            if(dividend == INT_MIN) return 1;
            else return 0;
        }
        
        int sign = 1;
        if((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) sign = -1;  // result sign
        if(divisor < 0) divisor = 0-divisor;  // modify to positive
        int count = 0;
        if(dividend>0)
        {
            while(dividend - divisor >=0 ) {
                dividend -= divisor;
                count++;
            }
        }
        else {
            while(dividend + divisor <=0 ) {
                dividend += divisor;
                count++;
            }
        }
        if(sign==-1) count = 0-count;
        return count;
    }

    void nextPermutationHelper(vector<int>& nums)
    {
        // 一个元素，直接返回
        if(nums.size()==1) return;
        
        // a[1:n] is biggest-least
        bool biggest = true;
        for(int i = 1; i < nums.size() - 1; i++)
            if(nums[i] < nums[i+1]) {
                biggest = false; break;
            }
        if(biggest) {
            int k = -1, value = 200;
            for(int i = 1; i < nums.size(); i++)
            {
                if(nums[i] > nums[0])  // 找比nums[0]大的最小值
                {   
                    if(nums[i] < value) {
                        value = nums[i]; 
                        k = i;
                    }
                }
            }
            // 交换nums[0]和比nums[0]大的最小值
            swap(nums[0], nums[k]);
            // nums[1:n]排序
            sort(nums.begin() + 1, nums.end());
            return;
        }
        // 删除首元素，得到nums[1:n]
        int front = nums.front();
        nums.erase(nums.begin());
        nextPermutationHelper(nums);
        nums.insert(nums.begin(), front);
    }

    void nextPermutation(vector<int>& nums) {
        bool biggest = true;
        for(int i = 0; i < nums.size() - 1; i++)
            if(nums[i] < nums[i+1]) {
                biggest = false;
                break;
            }
        // biggest-least to least-biggest
        if(biggest) {sort(nums.begin(), nums.end()); return;}
        
        nextPermutationHelper(nums);
    }
};

string replaceSpace(string s) {
    while(s.find(" ") != string::npos)
    {
        s.replace(s.find(" "), 1, "%20");
    }
    return s;
}

int binary_search(int *nums, int target, int len)
{
    int left = 0, right = len-1;
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if(nums[mid] == target) return mid;
        else if(target > nums[mid]) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int left_bound(vector<int> &nums, int target)
{
    // 搜索区间为[left, right)左闭右开区间
    int left = 0, right = nums.size();
    while(left < right)
    {
        int mid = (left + right) / 2;
        if(nums[mid] == target)  right = mid;   // 注意: 搜索左边界时，中间值=目标值时压缩右边界
        else if(target > nums[mid]) left = mid + 1;
        else if(target < nums[mid]) right = mid;
    }
    // 结束循环后left == right, 取值范围在[0, nums.size()]
    if (left == nums.size()) return -1;
    // left最终指向最左边的目标值(如果存在的话)
    return nums[left] == target ? left : -1;
}

int right_bound(vector<int> &nums, int target)
{
    // 搜索区间为[left, right)左闭右开区间
    int left = 0, right = nums.size();
    while(left < right)
    {
        int mid = (left + right) / 2;
        if(nums[mid] == target)  left = mid + 1;   // 注意: 搜索右边界时，中间值=目标值时压缩左边界
        else if(target > nums[mid]) left = mid + 1;
        else if(target < nums[mid]) right = mid;
    }
    // 结束循环后left == right, 取值范围在[0, nums.size()], 但是关注的是left-1
    if (left == 0) return -1;
    // left-1最终指向最右边的目标值(如果存在的话)
    return nums[left - 1] == target ? left - 1 : -1;
}

// 


int minArray(vector<int>& numbers) {
    int left = 0, right = numbers.size() - 1;
    // 注意循环终止条件为left == right
    while(left < right)
    {
        int mid = (left + right) / 2;
        if(numbers[mid] < numbers[right]) 
            right = mid;  // 旋转点在[left, mid]
        else if(numbers[mid] > numbers[right])
            left = mid + 1;  // 旋转点在[mid+1, right]
        else
            // right--;  // 此时无法判断旋转点在哪个区间,就让right-1
            {
                // 更快:转为线性查找
                int min = INT_MAX;
                for(int i = left; i <=right; i++)
                    if(numbers[i] < min) min = numbers[i];
                return min;
            }
    }
    return left;  
}

char firstUniqChar(string s) {
    unordered_map<char, int> m;
    // map<char, int> m;
    for(int i = 0; i < s.length(); i++)
        m[s[i]] += 1;
    for(int i = 0; i < s.length(); i++)
        if(m[s[i]] == 1) return s[i];
    return ' ';
}

int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        // 保证至少3元素
        while(left + 2 <= right) {
            cout << left <<' '<<right<<endl;
            int mid = (left+right) / 2;
            if(nums[mid] == target) return mid;
            if(nums[left] == target) return left;
            if(nums[right] == target) return right;
            int L = nums[left], M = nums[mid], R = nums[right];
            // 有四种情况target值在左侧
            if( (L<M && M<R && target<M) ||
                (R<L && M<R && target<M) || 
                (R<L && M<R && target>R) ||
                (R<L && L<M && target<M && target>=L))
                right = mid - 1;
            // 有四种情况target值在右侧
            else
                left = mid + 1;
        }
        for(int i = left; i <= right; i++)
            if(nums[i] == target) {
                return i;
            }
        return -1;
    }

int maxValue(vector< vector<int> >& grid) {
        // 还比较经典的一道题
        // dp[m,n] = max(dp[m,n-1],dp[n-1,m])+grid[m,n]
        // vp第一行、第一列特殊处理
        int m = grid.size(), n = grid[0].size();
        int dp[m][n];
        dp[0][0] = grid[0][0];
        for(int i = 1; i < n; i++)  dp[0][i] = dp[0][i-1] + grid[0][i];
        for(int i = 1; i < m; i++)  dp[i][0] = dp[i-1][0] + grid[i][0];
        for(int i = 1; i < m; i++)
        {
            for(int j = 1; j < n; j++)
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]) + grid[i][j];
        }
        return dp[m-1][n-1];
}

int lengthOfLongestSubstring(string s) {
    // f(i):以si为结尾的最长无重复字符子串长度，f(i) ∈ [1,f(i-1)+1]
    // g(i)=max{f(i)}
    // string last:以si为结尾的最长无重复字符子串
    if(s.length() == 1 || s.length() == 0) return s.length();
    int fi = 1, gi = 1;
    string last = s.substr(0, 1);
    for(int i = 1; i < s.length(); i++)
    {
        int x, index = last.find(s[i]);
        if(index==string::npos) x = fi;
        else x = last.length() - (index + 1);
        int newfi = x + 1;
        // update fi, gi, last
        if(newfi > gi) gi = newfi;
        fi = newfi;
        if(x == 0) last = string(1,s[i]);
        else last = last.substr(last.length() - x, x) + string(1,s[i]);
    }
    return gi;
}

int main()
{
    Solution s;
    
    int ints[] = {4,5,6,7,0,1,2};
    vector<int> a(ints, ints + sizeof(ints)/4);
    // s.nextPermutation(a);
    // for(int i = 0; i < a.size(); i++)
    //     cout << a[i] << ' ';
    // cout<<endl;
    // string str = "2 3 3 4";
    // cout << replaceSpace(str) << endl;
    // int list[] = {4, 4, 4, 4};
    // vector<int> b(list, list + sizeof(list)/4);
    // cout << minArray(b) << endl;

    // cout << firstUniqChar("ffaaddetf") << endl;
    int x = pow(2, 30);
    // cout << bitset<32>(x)<<endl << bitset<32>(-x)<<endl;
    cout << search(a, 0) << endl;
}