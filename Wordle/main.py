def trainer(wordlist, word, marker):
    """
    min, max, sum needs to be turned into a condition where it
    checks the previous element assuming it's not the first 
    and adds onto that value into another variable 
    [1, 2]
    2 checks 1, etc.
    """
    new_list = [0] * len(wordlist)
    list_placer = 0
    newer_list = []
    counter = 0
    newest_list = []
    answer = []
    word_counter = 0

    """
    for words in wordlist:  # O(N)
        for letters in word:  # O(M)
            if letters in words:
                new_list[list_placer] += 1
        list_placer += 1
    """

    while list_placer < len(wordlist): # O(N)
        current_letter = word[word_counter]
        if current_letter in wordlist[list_placer]: # O(M)
            new_list[list_placer] += 1  # this keeps the score of how many letters are in common

        word_counter += 1
        if word_counter == len(word):
            word_counter = 0
            list_placer += 1

    while counter < len(new_list):  # O(N)
        if new_list[counter] == len(word):
            newer_list.append(wordlist[counter])  # this list is all words with the same letters as the original word
            newest_list.append(0)  # this list is the score of how many letters are in the correct/incorrect place
            for identicals in newer_list[-1]:  # the wordlist[counter] is appended and iterated through in this for loop
                # this loop is the closest to O(X) I could have made it.
                letter_index = newer_list[-1].index(identicals)  # the index of the letter being iterated through
                if (word[letter_index] == identicals) and marker[newer_list[-1].index(identicals)] == 0:  # if both
                    # the original word and the appended word have the same letter in the same position but the marker
                    # indicates it as a "0" - add 1 to the score inside newest_list
                    newest_list[-1] += 1
                if (word[letter_index] == identicals) and marker[newer_list[-1].index(identicals)] == 1:
                    # otherwise, if it indicates it as a "1" - minus 1 to the score inside newest_list
                    newest_list[-1] -= 1

        counter += 1

    for minimum in newest_list:
        smol = min(newest_list)  # We find the minimum of the list as the lower the score, the more accurate it is
        # to the original word
        index_smol = newest_list.index(smol)  # Index of the lowest score.
        newest_list[newest_list.index(smol)] = max(newest_list)  # Replace the lowest score with the highest score
        if smol not in newest_list:  # So that we're able to find if there's any other number that matches the minimum

            if smol != sum(marker) * -1:  # If the value of smol is not equivalent to amount of correct letters
                # Then return an empty list as there's no valid words
                return []

            else:
                answer.append(newer_list[index_smol]) # Otherwise just append into the final list.
                print(answer)
                return answer

        answer.append(newer_list[index_smol]) # This occurs when there's another valid word


wordlist = ["costar", "carets", "recast", "traces", "reacts", "caster", "caters", "crates", "actors", "castor"]
word = "catrse"
marker = [1, 1, 0, 0, 0, 0]
trainer(wordlist, word, marker)
