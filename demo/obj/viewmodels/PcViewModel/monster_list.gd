extends ItemList

@export var pcViewModel : PcViewModel

@export var monster_img : TextureRect
@export var monster_name : Label
@export var monster_lvl : Label
@export var monster_crawd : Label
@export var monster_descr : RichTextLabel

func _ready():
	connect("item_selected", my_select)


func my_select(idx):
	print(idx)
	if(monster_img):
		monster_img.texture = pcViewModel.get_monster_img(idx)
		
	if(monster_name):
		monster_name.text = pcViewModel.get_monster_name(idx)
		
	if(monster_lvl):
		monster_lvl.text = pcViewModel.get_monster_lvl(idx)
		
	if(monster_descr):
		monster_descr.text = pcViewModel.get_monster_descr(idx)
	
	if(monster_crawd):
		monster_crawd.text = pcViewModel.get_monster_crowd_bonus(idx)
