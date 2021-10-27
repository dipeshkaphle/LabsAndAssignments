import xml.etree.ElementTree as Et

arr = [0, 50, 60, 63, 67, 70, 73, 77, 80, 85, 90, 101]
ranges = list(zip(arr[:-1], [x-1 for x in arr[1:]]))
grades = [0, 1, 2, 2.3, 2.5, 2.7, 3, 3.3, 3.7, 4, 4.5]
rev_mapper = {k: range(v[0], v[1]+1) for k, v in zip(grades, ranges)}
mapper = dict([item for sublist in [[(x, k) for x in v]
                                    for k, v in rev_mapper.items()] for item in sublist])


def main():
    tree = Et.parse('output.xml')
    root = tree.getroot()
    # Iterate through each element of root
    for sub_root in root:
        avg = 0.0
        count = 0
        temp = sub_root
        # Iterate over each sub-element
        for sub_sub_root in sub_root:
            # update marks
            sub_sub_root.text = str(int(sub_sub_root.text) + 5)
            # recalculate gpa
            gpa = mapper[int(sub_sub_root.text)]

            sub_sub_root.attrib['gpa'] = str(gpa)
            count += 1
            avg += gpa
            temp = sub_sub_root
        avg /= count
        temp.tail = "\n\t\t"
        c = Et.Element("average")
        c.text = str(avg)
        c.tail = "\n\t"
        sub_root.insert(count, c)

    # save updated xml to new_updated.xml
    tree.write('new_output.xml', encoding='utf-8', xml_declaration=True)


main()
