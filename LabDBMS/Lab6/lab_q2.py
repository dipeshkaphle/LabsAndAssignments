import xml.etree.ElementTree as et
arr = [0, 50, 60, 63, 67, 70, 73, 77, 80, 85, 90, 101]
ranges = list(zip(arr[:-1], [x-1 for x in arr[1:]]))
grades = [0, 1, 2, 2.3, 2.5, 2.7, 3, 3.3, 3.7, 4, 4.5]
rev_mapper = {k: range(v[0], v[1]+1) for k, v in zip(grades, ranges)}
mapper = dict([item for sublist in [[(x, k) for x in v]
                                    for k, v in rev_mapper.items()] for item in sublist])
tree = et.parse("score_data.xml")
print(tree)
root = tree.getroot()
#  Updating the XML
for elem_lv_1 in root:
    print(elem_lv_1.attrib)
    for elem_lv_2 in elem_lv_1:
        print("\t", elem_lv_2.tag, elem_lv_2.attrib, elem_lv_2.text)
        elem_lv_2.set("gpa", str(mapper[int(elem_lv_2.text)]))

# Converting it to string format
updated_xml = "<?xml version=\"1.0\"?>\n" + et.tostring(root).decode("utf-8")

# Writing it to a file
myfile = open("output.xml", "w")
myfile.write(updated_xml)
myfile.close()
