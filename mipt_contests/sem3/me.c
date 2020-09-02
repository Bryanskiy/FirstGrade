int count(const int *parr, int len, int value)
{
    int ans = 0;
    for(int i = 0; i < len; ++i)
    {
        if(parr[i] == value)
            ans += 1;
    }

    return ans;
}

int majority_element(const int *parr, int len)
{
    int ans1, ans2;
    int count1, count2;
    int ans;

    if(len == 1)
        return parr[0];

    ans1 = majority_element(parr, len / 2);
    ans2 = majority_element(parr + len / 2, len - len / 2);

    if(ans1 == ans2)
        return ans1;

    count1 = count(parr, len, ans1);
    count2 = count(parr, len, ans2);

    ans = (count1 > count2) ? ans1 : ans2;
    if(count(parr, len, ans) <= len / 2)
        return -1;

    return ans;
}
