#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
private:
    // Helper function to count the total number of nodes in the linked list
    int countNodes(ListNode* head) {
        int count = 0;
        while (head != nullptr) {
            count++;
            head = head->next;
        }
        return count;
    }

    // Recursive helper function using an inorder simulation strategy.
    // 'head' is passed by reference so that changes to the pointer persist across recursive calls.
    TreeNode* sortedListToBSTHelper(ListNode*& head, int start, int end) {
        // Base case: if boundaries cross, this subtree is empty
        if (start > end) {
            return nullptr;
        }

        int mid = start + (end - start) / 2;

        // Step 1: Recursively construct the left subtree.
        // In an inorder traversal, we process all elements in the left subtree first.
        TreeNode* leftChild = sortedListToBSTHelper(head, start, mid - 1);

        // Step 2: Construct the root node.
        // Once the left subtree is fully constructed, 'head' will be pointing 
        // to the node corresponding to the current 'mid' index.
        TreeNode* root = new TreeNode(head->val);
        root->left = leftChild;

        // Step 3: Advance the list pointer to process subsequent nodes.
        head = head->next;

        // Step 4: Recursively construct the right subtree.
        root->right = sortedListToBSTHelper(head, mid + 1, end);

        return root;
    }

public:
    TreeNode* sortedListToBST(ListNode* head) {
        // Find the length of the linked list
        int size = countNodes(head);
        
        // Build the BST using inorder simulation
        return sortedListToBSTHelper(head, 0, size - 1);
    }
};
