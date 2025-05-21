//
//  list.cpp
//  Homework4
//
//  Created by Cait on 5/14/23.
//

void listAll(const MenuItem* m, string path)  // two-parameter overload
{
//    preemptive pseudocode:
//    end case:
//        m->menuItems() == nullptr
//        return if this means there's nothing after
//    if m->MenuItem == nullptr and m->name != "" and there's no path before it
//        print the name and reutrn
//
//    going through vector
//            string placehold to store path to send to recusrive function
//            for( iterator = menu begin and then iterator != end, increase iterator)
//                if there's no path before
//                    placehold = name
//                if there's a path,
//                    placehold = path + / + name
//                and then print out the placehold and call listAll with the traverse at i and the placeholders
    if(m->menuItems() == nullptr) //end case
    {
        if(m->name() != "" && path == "")
        {
            cout << m->name() << endl;
        }
        return;
    }
    //going through branches
    string placehold; //to hold path to return to recusrive function
    const vector<MenuItem*>* traversal = m->menuItems(); //traverse through vector
    for(int i = 0; i < traversal->size(); i++)
    {
        if(path == "")
        {
            placehold = traversal->at(i)->name();
        }
        else
        {
            placehold = path + '/' + traversal->at(i)->name();
        }
        cout << placehold << endl;
        listAll(traversal->at(i), placehold);
    }
}
