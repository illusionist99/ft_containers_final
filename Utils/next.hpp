Node* Next(Node* node)
{
    // Make sure that the caller hasn't failed to stop.
    assert(node != nullptr);

    // If we have a right subtree we must iterate over it,
    // starting at its leftmost (minimal) node.

    if (node->right != nullptr)
        return Leftmost(node->right);
    
    // Otherwise we must go up the tree

    Node* parent = node->parent;
    if (parent == nullptr)
        return nullptr;

    // A node comes immediately after its left subtree

    if (node == parent->left)
        return parent;

    // This must be the right subtree!
    assert(node == parent->right);

    // In which case we need to go up again, looking for a node that is
    // its parent's left child.

    while (parent != nullptr && node != parent->left)
    {
        node = parent;
        parent = node->parent;
    }

    // We should be at a left child!
    assert(parent == nullptr || node == parent->left);

    // And, as we know, a node comes immediately after its left subtree

    return parent;
}