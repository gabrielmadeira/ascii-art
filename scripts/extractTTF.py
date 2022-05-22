from PIL import Image, ImageFont, ImageDraw

# use a truetype font

fontSize = 8
drawSize = 8

font = ImageFont.truetype(input("Font: "), fontSize)
im = Image.new("RGB", (fontSize, fontSize),(255,255,255))
draw = ImageDraw.Draw(im)

chars = ['$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*', 'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'Z' ,'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']', '?', '-', '+', '~', '<', '>', 'i', '!', 'l', 'I', ';', ':', ',', '\'', '^', '`', '"', '.', ' ']
#                                                          'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm', 'Z' ,'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '/',   '\\',   '|',   '(', ')',      '1', 'cbra', '}',     '[', ']',                             '?',     '-', '_',         '+',                        '~',   '<', '>',        'i', '!',  'l', 'I', ';',    ':',   ',',    '\'',    '^',   '`', '.', ' ']
charsFileName = ["dl", "at", "B", "perc", "8", "and", "W", "M", "hash", "ast", "o", "a", "h", "k", "b", "d", "p", "q", "w", "m", "Z" ,"O", "0", "Q", "L", "C", "J", "U", "Y", "X", "z", "c", "v", "u", "n", "x", "r", "j", "f", "t", "sla", "csla", "pip", "par", "cpar", "1", "cbra", "ccbra", "sbra", "csbra", "quest", "dash", "plus", "til", "less", "great", "i", "ex", "l", "I", "semc", "col", "comm", "singc", "car", "bco", "quot", "dot", "space"]
#'_',"unders",
print(str(len(chars)) + " " + str(len(charsFileName)));
for i in range(0, len(chars)):
  w, h = draw.textsize(chars[i], font=font)
 
  im = Image.new("RGB", (drawSize, drawSize),(255,255,255))
  draw = ImageDraw.Draw(im)
  draw.text(((drawSize-w)/2, (drawSize-h)/2), chars[i], font=font, fill="#000000")
  im.save("output/"+charsFileName[i] + ".png")