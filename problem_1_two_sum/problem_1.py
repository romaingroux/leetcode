class Solution:
    def twoSumNaive(self, nums: List[int], target: int) \
        -> List[int]:
        """
        Finds the index of two elements in nums that sum up 
        to target.
        Works in O(N^2)
        Args:
            nums: the list of values of interest.
            target: the target of interest.
        Returns:
            The index (0-based) of both values summing to target.
        """
        
        for i in range(0, len(nums)):
            for j in range(0, len(nums)):
                if i == j:
                    continue
                elif nums[i]+nums[j] == target:
                    return [i,j]
    
    def twoSumSort(self, nums: List[int], target: int) \
        -> List[int]:
        """
        Finds the index of two elements in nums that sum up 
        to target.
        Does not work if there are duplicated items in nums.
        Works in O(NlogN).
        Args:
            nums: the list of values of interest.
            target: the target of interest.
        Returns:
            The index (0-based) of both values summing to target.
        """
        # keep track of the original index for nums values
        idx_map = {n:i for i,n in enumerate(nums)}

        # sort
        nums = sorted(nums)
        l = len(nums)
        i = 0
        j = l-1

        while (i < j):
            s = nums[i] + nums[j]
            # exact match
            if s == target:
                return [idx_map[nums[i]],idx_map[nums[j]]]
            # undershoot, increase lower (left) value
            elif s < target:
                i += 1
            # elif s > target:
            # overshoot, decrease upper (right) value
            else:
                j -= 1
    
    def twoSum(self, nums: List[int], target: int) \
        -> List[int]:
        """
        Finds the index of two elements in nums that sum up 
        to target.
        Args:
            nums: the list of values of interest.
            target: the target of interest.
        Returns:
            The index (0-based) of both values summing to target.
        """

        # contains each value and its index in nums
        d = {num:i for i,num in enumerate(nums)}
        
        # for each item, search if nums[i] + diff = target exists
        # by looking in dict
        for i,num in enumerate(nums):
            # this is the value nums should contains for nums[i] to sum up with 
            # something
            diff = target - num
            if d.get(diff, None) is not None:
                j = d[diff]
                if i != j:
                    return [i,d[diff]]
        return []