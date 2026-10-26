#define NOB_IMPLEMENTATION
#include "nob.h"

#include <assert.h>
#include <stdio.h>

typedef struct TrieNode {
    char character;
    // Optional value
    size_t value;

    struct {
        size_t count;
        size_t capacity;
        struct TrieNode* items;
    } children;
} TrieNode;

typedef struct {
    size_t count;
    size_t capacity;
    Nob_String_View* items;
} StringDa;

TrieNode* trie_find_char(TrieNode* node, char c) {
    for (size_t i = 0; i < node->children.count; ++i) {
        TrieNode* currentNode = &node->children.items[i];
        if (currentNode->character == c) {
            return currentNode;
        }
    }
    return NULL;
}

void trie_add_word(TrieNode* root, Nob_String_View word) {
    TrieNode* currentNode = root;
    for (size_t i = 0; i < word.count; ++i) {
        char c = word.items[i];
        TrieNode* node = trie_find_char(currentNode, c);
        
        if (node == NULL) {
            TrieNode newNode = {0};
            newNode.character = c;
            nob_da_append(&currentNode->children, newNode);
        }
        node = trie_find_char(currentNode, c);
        assert(node != NULL && "How is the node still NULL");
        currentNode = node;
    }
}

void trie_stringify_branches(const TrieNode* node, Nob_String_View prefix, StringDa* da) {
    Nob_String_Builder sb = {0};
    nob_sb_append_buf(&sb, prefix.data, prefix.count);
    if (node->character) nob_da_append(&sb, node->character);
    Nob_String_View sv = nob_sb_to_sv(sb);

    if (node->children.count == 0) {
        nob_da_append(da, sv);
        return;
    }
    for (size_t i = 0; i < node->children.count; ++i)
        trie_stringify_branches(&node->children.items[i], sv, da);
    nob_sb_free(sb);
}

StringDa trie_get_completions(TrieNode* root, Nob_String_View chars) {
    TrieNode* currentNode = root;
    StringDa da = {0};

    for (size_t i = 0; i < chars.count; ++i) {
        char c = chars.items[i];
        TrieNode* node = trie_find_char(currentNode, c);
        if (node == NULL) {
            return da;
        }
        currentNode = node;
    }

    for (size_t i = 0; i < currentNode->children.count; ++i) {
        trie_stringify_branches(&currentNode->children.items[i], chars, &da);
    }
    return da;
}

int main(void) {
    TrieNode rootNode = {0};
    trie_add_word(&rootNode, SVLIT("Hello"));
    trie_add_word(&rootNode, SVLIT("Helium"));
    trie_add_word(&rootNode, SVLIT("Apple"));

    StringDa da = trie_get_completions(&rootNode, SVLIT("He"));

    for (size_t i = 0; i < da.count; ++i) {
        printf("Completion: "SV_Fmt"\n", SV_Arg(da.items[i]));
    }

    return 0;
}
