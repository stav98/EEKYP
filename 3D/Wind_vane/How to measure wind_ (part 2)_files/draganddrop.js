function positionObject(int_x,int_y){this.x=int_x;this.y=int_y;}
function GetEventPosition(event){var x,y;if(event.changedTouches){x=event.changedTouches[0].pageX;y=event.changedTouches[0].pageY;}else{x=event.PageX;y=event.PageY;if(!x){x=event.clientX+document.body.scrollLeft;y=event.clientY+document.body.scrollTop;}}
return new positionObject(x,y);}
function EnableDrag(var_element,onDragMove,onDragEnd){if(document.addEventListener){var_element.addEventListener("mousedown",Drag_start,false);var_element.addEventListener("touchstart",Drag_start,false);}else if(document.attachEvent){var_element.attachEvent("onmousedown",Drag_start);}
if(onDragMove)var_element.onDragMove=onDragMove;if(onDragEnd)var_element.onDragEnd=onDragEnd;}
var LastDraggedObject=null;function DraggedObject(obj_element,obj_elmtInitialPos,obj_mouseInitalPos){this.element=obj_element;this.elmtInitialPos=obj_elmtInitialPos;this.elmtCurrentPos=new positionObject(obj_elmtInitialPos.x,obj_elmtInitialPos.y);this.mouseInitialPos=obj_mouseInitalPos;}
function Drag_start(event){if(!event)event=window.event;var source=event.srcElement;if(event.button!=undefined){if((event.which||event.button)!=1){return false;}}
if(!source)source=this;if(!source){return false;}
var originalsource=source;while(source.tagName!="DIV"){if(source.tagName=="A"){return false;}
source=source.parentNode;}
if(source.id!=this.id){return false;}
if(event.preventDefault){event.preventDefault();}
source.style.cursor="move";lastDraggedObject=new DraggedObject(source,new positionObject(parseInt(source.style.left),parseInt(source.style.top)),GetEventPosition(event));if(document.addEventListener){document.addEventListener("mousemove",Drag_mouseCapture,false);document.addEventListener("mouseup",Drag_stopMouseCapture,false);document.addEventListener("touchmove",Drag_mouseCapture,false);document.addEventListener("touchend",Drag_stopMouseCapture,false);}else if(document.attachEvent){document.attachEvent("onmousemove",Drag_mouseCapture);document.attachEvent("onmouseup",Drag_stopMouseCapture);}
document.onmouseup=Drag_stopMouseCapture;return true;}
function Drag_mouseCapture(event){if(!event)event=window.event;var position=GetEventPosition(event);if(event.preventDefault)event.preventDefault();var x=(lastDraggedObject.elmtInitialPos.x+position.x-lastDraggedObject.mouseInitialPos.x);var y=(lastDraggedObject.elmtInitialPos.y+position.y-lastDraggedObject.mouseInitialPos.y);var iw=getInnerWidth()
var ih=getInnerHeight();var w=lastDraggedObject.element.offsetWidth;var h=lastDraggedObject.element.offsetHeight;if(x>iw-w)x=iw-w;if(y>ih-h)y=ih-h;if(x<0)x=0;if(y<0)y=0;var p={x:x,y:y};if(lastDraggedObject.element.onDragMove)
lastDraggedObject.element.onDragMove(lastDraggedObject.element,p);lastDraggedObject.elmtCurrentPos.x=p.x;lastDraggedObject.elmtCurrentPos.y=p.y;lastDraggedObject.element.style.left=p.x+"px";lastDraggedObject.element.style.top=p.y+"px";}
function Drag_stopMouseCapture(){if(document.removeEventListener){document.removeEventListener("mousemove",Drag_mouseCapture,false);document.removeEventListener("mouseup",Drag_stopMouseCapture,false);document.removeEventListener("touchmove",Drag_mouseCapture,false);document.removeEventListener("touchend",Drag_stopMouseCapture,false);}else if(document.detachEvent){document.detachEvent("onmousemove",Drag_mouseCapture);document.detachEvent("onmouseup",Drag_stopMouseCapture);}
if(lastDraggedObject){lastDraggedObject.element.style.cursor='default';if(lastDraggedObject.element.onDragEnd)
lastDraggedObject.element.onDragEnd(lastDraggedObject.element,{x:lastDraggedObject.elmtCurrentPos.x,y:lastDraggedObject.elmtCurrentPos.y});}
lastDraggedObject=null;}