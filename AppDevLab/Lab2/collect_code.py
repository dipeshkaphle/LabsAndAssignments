import os

from markdown import markdown
markdown_content = ''


for root, dirs, files in os.walk("./"):
    for file in files:
        if(file.endswith('.java')):
            markdown_content+= ">File: {}\n\n".format(os.path.join(root,file))
            file_content = open(os.path.join(root, file), 'r')
            markdown_content += "```java\n"
            markdown_content += file_content.read()
            markdown_content += "```\n"
            file_content.close()



open('code.md','w').write(markdown_content)
