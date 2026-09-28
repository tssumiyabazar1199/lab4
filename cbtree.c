#include "DS.h"

/*
  p-ийн зааж буй CBTree-д x утгыг оруулна
*/
void cb_push(CBTree *p, int x)
{
	if (p->cb_len >= 100) return;
	p->cb_arr[p->cb_len] = x;
	p->cb_len++;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны зүүн хүүгийн индексийг буцаана.
  Зүүн хүү байхгүй бол -1 буцаана.
*/
int cb_left(const CBTree *p, int idx)
{
	int l = 2 * idx + 1;
	if (l < p->cb_len)
		return l;
	return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройны баруун хүүгийн индексийг буцаана.
  Баруун хүү байхгүй бол -1 буцаана.
*/
int cb_right(const CBTree *p, int idx)
{
	int r = 2 * idx + 2;
	if (r < p->cb_len)
		return r;
	return -1;
}

/*
  p-ийн зааж буй CBTree-с x тоог хайн
  хамгийн эхэнд олдсон индексийг буцаана.
  Олдохгүй бол -1 утгыг буцаана.
*/
int cb_search(const CBTree *p, int x)
{
	int i;
	for (i = 0; i < p->cb_len; i++) {
		if (p->cb_arr[i] == x)
			return i;
	}
	return -1;
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй зангилаанаас дээшхи бүх өвөг эцэгийг олох үйлдлийг хийнэ.
  Тухайн орой өөрөө өвөг эцэгт орохгүй.
  Өвөг эцэг бүрийг нэг шинэ мөрөнд хэвлэнэ. Өвөг эцэгийг доороос дээшхи дарааллаар хэвлэнэ.
*/
void cb_ancestors(const CBTree *p, int idx)
{
	if (idx <= 0 || idx >= p->cb_len) return;
	int parent = (idx - 1) / 2;
	while (parent >= 0) {
		printf("%d\n", p->cb_arr[parent]);
		if (parent == 0) break;
		parent = (parent - 1) / 2;
	}
}

/*
  p-ийн зааж буй CBTree-ийн өндрийг буцаана
*/
int cb_height(const CBTree *p)
{
	if (p->cb_len == 0) return 0;
	int h = 0;
	int count = p->cb_len;
	while (count > 0) {
		h++;
		count /= 2;
	}
	return h;
}

/*
  p-ийн зааж буй CBTree-д idx оройны ах, дүү оройн дугаарыг буцаана.
  Тухайн оройн эцэгтэй адил эцэгтэй орой.
  Ах, дүү нь байхгүй бол -1-г буцаана.
*/
int cb_sibling(const CBTree *p, int idx)
{
	if (idx <= 0 || idx >= p->cb_len) return -1;
	int parent = (idx - 1) / 2;
	int l = 2 * parent + 1;
	int r = 2 * parent + 2;

	if (idx == l) {
		if (r < p->cb_len) return r;
	} else if (idx == r) {
		if (l < p->cb_len) return l;
	}
	return -1;
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн preorder-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_preorder(const CBTree *p, int idx)
{
	if (idx < 0 || idx >= p->cb_len) return;
	printf("%d\n", p->cb_arr[idx]);
	cb_preorder(p, cb_left(p, idx));
	cb_preorder(p, cb_right(p, idx));
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн in-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
*/
void cb_inorder(const CBTree *p, int idx)
{
	if (idx < 0 || idx >= p->cb_len) return;
	cb_inorder(p, cb_left(p, idx));
	printf("%d\n", p->cb_arr[idx]);
	cb_inorder(p, cb_right(p, idx));
}

/*
  p-ийн зааж буй CBTree-г idx дугаартай зангилаанаас эхлэн post-order-оор хэвлэ.
  Орой бүрийг нэг шинэ мөрөнд хэвлэнэ.
 */
void cb_postorder(const CBTree *p, int idx)
{
	if (idx < 0 || idx >= p->cb_len) return;
	cb_postorder(p, cb_left(p, idx));
	cb_postorder(p, cb_right(p, idx));
	printf("%d\n", p->cb_arr[idx]);
}

/*
  p-ийн зааж буй CBTree-с idx дугаартай зангилаанаас доошхи бүх навчийг олно.
  Навч тус бүрийн утгыг шинэ мөрөнд хэвлэнэ.
  Навчыг зүүнээс баруун тийш олдох дарааллаар хэвлэнэ.
*/
void cb_leaves(const CBTree *p, int idx)
{
	if (idx < 0 || idx >= p->cb_len) return;
	int l = cb_left(p, idx);
	int r = cb_right(p, idx);

	if (l == -1 && r == -1) {
		printf("%d\n", p->cb_arr[idx]);
		return;
	}
	if (l != -1) cb_leaves(p, l);
	if (r != -1) cb_leaves(p, r);
}

/*
  p-ийн зааж буй CBTree-д idx индекстэй оройноос доошхи бүх үр садыг хэвлэнэ.
  Тухайн орой өөрөө үр сад болохгүй.
  Үр, сад бүрийг нэг шинэ мөрөнд хэвлэнэ. Үр садыг pre-order дарааллаар хэлэх ёстой.
*/
void cb_descendants(const CBTree *p, int idx)
{
	if (idx < 0 || idx >= p->cb_len) return;
	int l = cb_left(p, idx);
	int r = cb_right(p, idx);

	if (l != -1) cb_preorder(p, l);
	if (r != -1) cb_preorder(p, r);
}

/*
  p-ийн зааж буй Tree-д хэдэн элемент байгааг буцаана.
  CBTree-д өөрчлөлт оруулахгүй.
*/
int cb_size(const CBTree *p)
{
	return p->cb_len;
}

/*
  p-ийн зааж буй CBTree-д x утгаас үндэс хүртэлх оройнуудын тоог буцаана.
  x тоо олдохгүй бол -1-г буцаана.
*/
int cb_level(const CBTree *p, int x)
{
	int idx = cb_search(p, x);
	if (idx == -1) return -1;

	int level = 0;
	while (idx > 0) {
		level++;
		idx = (idx - 1) / 2;
	}
	return level;
}