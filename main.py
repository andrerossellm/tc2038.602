from sais import sais

string = "andre quizas$"
T = [ord(c) for c in string]
SA = sais(T)
print(SA)