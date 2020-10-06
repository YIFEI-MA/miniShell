import spacy
from spacy import displacy

nlp = spacy.load("en_core_web_sm")
doc = nlp("What We Know About Breonna Taylor’s Case and Death.")

for token in doc:
    print(token.text,"\t",token.lemma_, "\t", token.pos_, "\t", token.tag_, "\t", token.dep_, "\t",
            token.shape_, "\t",token.is_alpha, "\t",token.is_stop)
displacy.serve(doc, style="dep", options={'fine_grained':True})
