# **Easy Combo-box in list under Qt**

## The Goals

Qt is a powerful framework to build the user interface of desktop applications. Yet, sometimes , it is hard to unite all the necessary
information on how to achieve a particular goal. It can be frustrating to feel that the solution is close at hand and yet things
don't work properly.

I recently wanted to put a combo-box widget inside the items of a table list. While the standard way of doing this is simple, the
results are not satisfying. I wanted to improve the usual solution to make the experience more pleasant for the user. I searched for
all-made solutions on the internet. While I found some ideas in the Qt wiki and on stack overflow there was not a complete solution that worked to my satisfaction.

That's why I want to share the solution that I finally cracked recently. Here’s what I wanted to do and why.

1. I wanted to put a combo-box directly in a multi-column table list widget.  
  
**Why**: to be able to rapidly change a value for an item in the list. This is actually not hard and there are examples directly in the Qt
	documentation. 
  
2. I wanted the combo-box to always be visible.  
  
**Why**: so the user would know the	item was editable directly. By default, Qt keeps the combo-box
	hidden. Qt requires the user to double-click the item to show the
	combo-box. This is not easily to discover by the average user. The
	result is that the user does not even know that an item is editable! 
  
3. I wanted the combo-box to show	the content of the combo-box on the first click.  
  
**Why**: normally, in Qt, the first click is used to select the item in the
	list. On the other hand, for normal combo-box, the first click shows
	its contents. This discrepancy in behavior makes the combo-box
	integrated in the list work differently than a combo-box outside of
	a list. It feels abnormal for the user. 
  
4. I wanted the click on the combo-box to select the table row.  
  
**Why**: normally, the combo-box click would be absorbed by the combo-box and the row
	would not be selected, which would confuse the user. 
  
5. I wanted the combo-box to end the item edition as soon as the user selects an item.  
  
**Why**: normally, Qt leaves the list item in editing mode until the user
	moves away from the item with the keyboard or by clicking elsewhere.
	Again, this is inconsistent compared to how the combo-box works
	outside a list view. 

## The Solution

Here is how each goal is achieved.

1. Put the combo-box directly in the multi-column list widget.  
  
**How**: using a QStyledItemDelegatethat creates a combo-box as its editor.
	This is standard Qt code and is shown in the Qt wiki.
	 
2. Make the combo-box always visible.  
  
**How**: This is also standard Qt code: override the paintand the sizeHint
	functions of the delegate.The 	problem is that the exact
	code necessary is not obvious from the documentation. Particularly,
	getting the standard style is not obvious.  See
	the code on github for the details. 
  
3. Show	the content of the combo-box on the first click.  
  
**How**: This requires three tricks.	The first is to override themousePressEvent
	function of the table widget. This allows entering editing mode on
	the first mouse click. In the mousePressEvent
	function, we fire up a single-shot timer that calls the edit
	function of the table widget with the selected item index. (Using a
	timer is required so that the trick for selecting the row will work
	later on.) The second is to pre-select the current item in the
	combo-box with a call to setCurrentIndexwithin the setEditorDatafunction of the delegate. The
	third is to call the showPopup function of the combo-box so that it shows it content immediately,
	again the in the setEditorData function. 
  
4. Select	the table row with	the click on the combo-box.  
  
**How**:	we need to both select the row and fire up	the editor. That’s
	why we delay showing the editor, otherwise the row selection would
	interfere. So, in the mousePressEvent	function, we call setCurrentIndexon the table selection model. 
  
5. End the item edition as soon as the user selects an item.  
  
**How**: In the createEditor	function of the delegate, when we create the combo-box, we
	immediately connect to its currentTextChanged	signal. The connected function commit the data and end the editor.
	This is done by calling the commitData	and the closeEditor	function of the delegate. 

## The Code

The C++ code needed to have an always-present combo-box in a table widget is available in this public repository on github:

[https://github.com/pierrebai/QtAdditions](https://github.com/pierrebai/QtAdditions)

The example is provided as a CMake project that generates a Visual Studio 2019 solution.
