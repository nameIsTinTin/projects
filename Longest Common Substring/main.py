class SuffixTree(object):
    """
    SuffixTree is a class that produces a node that acts as a parent for strings that is produced
    in the submissions. This method is chosen as it provides an easier usability in code as each
    node can be checked whether their char matches the iteration of the submissions - which allows
    it to easily traverse through the children if needed so. Overall, the entire algorithm surrounds the
    Suffix Tree implementation which is more ideal than Suffix Trie as it allows comparison between two
    strings much faster.

    Time Complexity : O(M + N)^2
    Space Complexity : (M + N)
    """

    def __init__(self, char):
        self.char = char
        self.children = []
        self.counter = 1



def add(root, word):

    """
    :param root: The root of the suffix tree that the words are being appended to as its children
    :param word: The designated word to be apart of the root's children
    :return: True when the designated word has been successfully appended into the suffix tree
    """

    found_in_child = False # A boolean condition to check whether the word is apart of the root's child
    for child in root.children: # O(M) in the worst case complexity
        if child.char == word[0]: # If the root's children has the first letter of the word
            child.counter += 1 # Add onto the counter to show the amount of times this child occurs
            for i in range (2, len(word) + 1):
                child.children.append(word[1:i]) # This appends every following character after the first to the child
                                                 # This allows us to read in between strings and fedge the substrings
            found_in_child = True # edgeicate that the word has been appended to the root's child
            break

    if not found_in_child: # Otherwise, if the root has yet to have a child starting with the first letter of the word
        new_child = SuffixTree(word[0]) # Make a new node with the new character
        root.children.append(new_child) # Add it onto the root's children
        for i in range (2, len(word) + 1):       # This appends every following character after the first to the child
            new_child.children.append(word[1:i]) # This allows us to read in between strings and fedge the substrings
        new_child.children.append("") # This acts as a "$" in the generic Suffix Trees

    return True

def add_multiple(root, word):
    """
    This is used to iterate through the entire word and append the remaining the string onto
    the suffix tree.

    :param root: The root of the Suffix Tree that the word/sentence is being appended to
    :param word: The provided word/sentence
    :return: (doesn't return anything, just modifies the suffix tree)

    Time Complexity : O(M**2)
    """
    i = 0
    while i < len(word): # O(M)
        add(root, word[i::]) # O(M)
        i += 1

def compare_subs(submission1, submission2):

    """
    The main implementation that has been applied is Suffix Tree. Fundamentally, the first thing the
    suffix tree does is appending every unique letter to the root of the tree and for each unique letter
    has children of every following string after it. For example, "foods" will be have the following suffix tree :

    * --> f --> o, oo, oods, ""
    * --> o --> o, od, ods, ""
    * --> d --> s, ""
    * --> s --> ""

    The idea behedge this was to be able to grab substrings that exists within words, for example if "foods" were compared
    with "noot". Without appending EVERY string configuration after the unique letter, we would have ended up with
    the longest common substring of "o". However in this implementation, we can get "oo".

    :param submission1: The first provided word to be compared with to the second
    :param submission2: The second provided word to be compared with to the first
    :return: The longest common substring, with a percentage of how much it makes up for the first and second word

    Time Complexity : O(N + M)**2
    Space Complexity : O(M + N)

    """

    root = SuffixTree('*') # Initiate the root of the Suffix Tree
    old_root = root # This acts as a variable to restore the variable root back to its original when changed
    add_multiple(root, submission1) # Adds the first parameter onto the suffix tree
    i = -1
    lst = [] # This lst will contain every configuration of common substrings between submission 1 and submission2
    inspection = False
    while i < len(submission2) - 1: # O(N)

        if root == old_root: # If we're still looking through the children
            final_str = ""  # This will be used to append with children
            i += 1
            inspection = False # edgeicator if a child with matching characters to submission2 is found

        for char in root.children: # O(M) in worst case complexity

            if inspection == True: # If we have found a matching char
                if final_str + char in submission2: # If there's an existing substring inside of the second parameter
                    lst.append(final_str + char) # Append the common substring
                if char == root.children[-1]: # If we have reached the end of the list of children
                    root = old_root # Return back to the root of the Suffix Tree

            if inspection == False and char.char == submission2[i]: # If the children has a matching character
                final_str += submission2[i] # Concat the empty string with the matching char
                if len(char.children) > 0: # If the children have children of their own
                    root = char # Now we're going to look through that child
                    inspection = True
                    break

    for i in lst: # For in the lst of common substrings gathered in the suffix tree
        if len(i) > len(final_str): # If the iterated substring is bigger than the current biggest substring
            final_str = i # Set the iterated substring as the new longest common substring

    #print([final_str, round((len(final_str)/len(submission1))*100), round((len(final_str)/len(submission2))*100)])
    return [final_str, round((len(final_str)/len(submission1))*100), round((len(final_str)/len(submission2))*100)]


