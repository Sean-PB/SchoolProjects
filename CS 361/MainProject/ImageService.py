import os

# Read text file
read_file = open('image_pipeline.txt', 'r')
data = read_file.readline()
read_file.close()

# Parse card from text and generate file path
card = data.split(':')
file_path = os.getcwd() + "/images/" + card[0] + card[1] + ".png"

# Write file path to text file
write_file = open('image_pipeline.txt', 'w')
write_file.write(file_path)
write_file.close()