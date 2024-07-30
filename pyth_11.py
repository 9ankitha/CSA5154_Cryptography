from collections import Counter
import math

def minGroups(nums):
    # Count the frequency of each value
    frequency = Counter(nums)
    
    # Determine the maximum number of groups needed
    max_groups = 0
    for count in frequency.values():
        # Calculate groups needed for this value
        groups_needed = math.ceil(count / 2)
        max_groups = max(max_groups, groups_needed)
    
    return max_groups

# Example usage:
nums = [3, 2, 3, 2, 3]
print(minGroups(nums))  # Output: 2
