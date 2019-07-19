import nltk


class Analyzer():
    """Implements sentiment analysis."""

    # loads positive and negative words into memory in such a way that analyze can access them, and
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        # TODO

        # set is like a list..?
        #self.positive_words = set()
        self.positive_words = set()
        self.negative_words = set()

        self.score = 0

        #print("positives are: ", positives)

        # could be a function to load files..
        positive_file = open(positives, "r")

        for line in positive_file:
            self.positive_words.add(line.rstrip("\n"))

        # close flie resource
        positive_file.close()

        negative_file = open(negatives, "r")

        for line in negative_file:
            self.negative_words.add(line.rstrip("\n"))

        # close flie resource
        positive_file.close()

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        if(text.lower() in self.positive_words):
            #print("we have a positive match!", text)
            self.score += 1
            #print(self.score)

        elif(text.lower() in self.negative_words):
            #print("we have a negative match!")
            self.score -= 1
        #print("text received: ", text)

        # compare text to stored text
        # if found, score++

        return self.score
