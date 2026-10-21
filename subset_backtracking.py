def subsets(input) -> list[list[int]]:
    res = []
    # subset = []

    def dfs(index, subset):
        # print(index)
        if index >= len(input):   
            res.append(subset.copy())
            return

        subset.append(input[index])
        dfs(index+1, subset)

        subset.pop()
        dfs(index+1, subset)

    dfs(0, [])
    return res


res = subsets([1,2,3])
print(res)




