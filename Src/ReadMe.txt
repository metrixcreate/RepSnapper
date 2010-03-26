

RepSnapper is released under the terms of the MIT license. (http://www.opensource.org/licenses/mit-license.php)



You need CGAL 3.5 or higher. Get it here: http://gforge.inria.fr/frs/?group_id=52


Read this

Todo:

Shrinking: look for minkowski sum

Fix printing of objects where the called-for thickness of the part is less than twice the filament extrusion. - with one line only
Batch conversion
Load many objects, place them on as few prints as possible (considering the print surface size)
Arrays of objects (load one, print 4)


[00:49]	<jonored>	(Find the convolution cycle, break all edges that intersect into edges that meet at the intersection point, and then use the winding number around a point on either side of each edge to determine whether to keep the edge.
[00:50]	<jonored>	I'm not using them either, but they describe how to do it well enough to write the code...

[00:36]	<jonored>	I mean, where the called-for thickness of the part is less than twice the filament extrusion.
[00:36]	<jonored>	*width
[00:36]	<Kulitorum>	Ah... I have'nt thougt about that
[00:36]	<Kulitorum>	Print it with one line?
[00:36]	<Kulitorum>	I can do that
[00:36]	<jonored>	Well, it's just another edge case that should be considered...
[00:37]	<Kulitorum>	I have put it on the todo-list :)
[00:37]	<jonored>	I'm actually insetting by the full width of the filament, and then outsetting by one-half the filament width for mostly that reason.
[00:38]	<Kulitorum>	I was considering shrinking the object by half the diameter of the filament extrusion anyway, I guess that should be handeling that too.
[00:38]	<Kulitorum>	Inserting - shrinking 1, then un-shrinking 0.5 ?
[00:39]	<jonored>	that's so that the code to remove lines that aren't actually on the boundary of the solid removes that kind of thing.
[00:39]	<Kulitorum>	Do you do intersection tests after shrinking it?
[00:39]	<jonored>	Yep.
[00:39]	<Kulitorum>	Right.
[00:39]	<Kulitorum>	...In what code? - is it available?
[00:39]	<jonored>	It's common lisp code that I've written.
[00:39]	<Forrest_Higgs>	enigma
[00:39]	<jonored>	Still has some edge cases that I need to find and fix, though, so...
[00:40]	<Kulitorum>	ok.


