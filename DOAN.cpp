#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

struct MonAn {
	char Name[25];
	long long Price;
};

struct LuaChon {
	int ChonMon;
	int SoLuong;
};

void Gioithieu() {
	printf("\t==================================================================================================\n");
	printf("\t||                                        DO AN CO SO                                           ||\n");
	printf("\t||\t\tDe tai: XAY DUNG UNG DUNG DAT MON AN VA THANH TOAN DON HANG \t\t\t||\n");
	printf("\t||\t\tSinh vien thuc Hien: Phan Duc Thinh   lop: 19TCLC_NHAT1      \t\t\t||\n");
	printf("\t||\t\tGiao vien huong dan: Tran Ho Thuy Tien                      \t\t\t||\n");
	printf("\t==================================================================================================\n");
	system("pause>nul");
	system("Cls");
}

int KtraSoNguyen() {
	char nhap[20], chuoi[20];
	int so, dem=0;
	do{
		if(dem>0) printf("-Nhap khong hop le. Vui long nhap lai:");
		scanf("%s", &nhap);
		so = atoi(nhap);
		itoa(so, chuoi, 10);
		dem++;
	}
	while (strcmp(chuoi, nhap) != 0);
	return so;
}
int NhapMagiaodich(int magiaodich){	
	printf("-Vui long nhap ma giao dich: ");
	magiaodich = KtraSoNguyen();
	while(magiaodich!=102190338){
		printf("-Ma giao dich khong dung.\n");
		printf("-Vui long nhap lai ma giao dich: ");
		magiaodich = KtraSoNguyen();
	};
	return magiaodich;
}

void Maketthucngay(){
	char Maketthuc[100];
	printf("-Nhap ma giao dich de ket thuc ngay: ");scanf("%s",&Maketthuc);
	while(strcmp(Maketthuc, "102190338")){
		printf("-Ma khong hop le!\n-Vui long nhap lai : ");scanf("%s",&Maketthuc);
	}
}

void printMenu(MonAn a[]) {
	printf("\n=============== MENU ================\n");
	printf("%-4s|%-20s |%s", "ID", "        Ten Mon", "Gia");
	printf("\n----|---------------------|----------");
	for(int i=0; i<11; i++) {
		printf("\n%-4d|%-20s |%d VND",i+1, a[i].Name, a[i].Price);
	}
	printf("\n-------------------------------------");
	printf("\n========Nhap 0 0 de ket thuc!========\n");	
}


void ChonMon(LuaChon luachon[], int &dem)  {
	for(dem=0; dem<5; dem++) {
		printf("Lua chon %d: ", dem+1); 
		luachon[dem].ChonMon = KtraSoNguyen();
		luachon[dem].SoLuong = KtraSoNguyen();
		fflush(stdin);
		if(luachon[dem].ChonMon == 0 && luachon[dem].SoLuong == 0) break;
		if(luachon[dem].ChonMon > 11 || luachon[dem].ChonMon <= 0) {
			printf("-Xay ra loi! vui long nhap lai!\n");
			dem--;
		}
		if(luachon[dem].SoLuong>100 || luachon[dem].SoLuong<0) {
			printf("-Chuong trinh gioi han so luong! Vui long nhap lai!\n");
			dem--;
		}
		else for(int j=0; j<dem; j++) {
				if(luachon[j].ChonMon == luachon[dem].ChonMon) {
					luachon[j].SoLuong += luachon[dem].SoLuong;
					dem--;
				}
			}
	}
}

void printLuaChon(MonAn a[], LuaChon luachon[], int dongia[], int dem, long long &Tong) {
	printf("\n%-20s| %-9s|%12s\n", "Ten Mon", "So luong", "Gia");
	printf("--------------------|----------|-------------------\n");
	for(int i=0; i<dem; i++) {
		dongia[i] = a[luachon[i].ChonMon-1].Price * luachon[i].SoLuong;
		Tong += dongia[i];
		printf("%-20s|   %-7d|%15d VND\n", a[luachon[i].ChonMon-1].Name, luachon[i].SoLuong, dongia[i]);
	}
	printf("---------------------------------------------------\n");
	printf("-Tong:%41lld VND\n", Tong);
}

void TinhTien(long long &Tong, long long &discout){
	if(Tong < 2000000) {
		printf("-Giam gia: %36lld VND\n", discout);
		printf("-Tong tien phai tra: %26lld VND\n", Tong);
	}
	else {
		discout = Tong*25/100;
		Tong = Tong*75/100;
		printf("-Giam gia: %36lld VND\n-Tong tien phai tra: %26lld VND", discout, Tong);
	}
}
void ghiFile(FILE *file, MonAn a[], LuaChon luachon[], int dongia[], int dem, long long Tong, long long discout, int madonhang, int magiaodich) {	
	file = fopen("D:\\Lichsu.txt","a");
	fprintf(file, "-Ma giao dich: %d\n", magiaodich);
	fprintf(file, "-Ma don hang: %d\n", madonhang);
	fprintf(file, "%-20s| %-9s|%12s\n", "Ten Mon", "So luong", "Gia");
	fprintf(file, "--------------------|----------|-------------------\n");
	for(int i=0; i<dem; i++) {
		fprintf(file, "%-20s|   %-7d|%15d VND\n", a[luachon[i].ChonMon-1].Name, luachon[i].SoLuong, dongia[i]);
	}
	fprintf(file, "---------------------------------------------------\n");
	fprintf(file, "-Tong:%41lld VND\n-Giam gia: %36lld VND\n-Tong tien phai tra: %26lld VND\n\n\n", Tong+discout, discout, Tong);
	fclose(file);
}
int main() {
	MonAn a[12];
	LuaChon luachon[5];
	int dongia[10], dem, end, magiaodich, madonhang=1;
	long long Tong=0, discout=0;
	FILE *file;
	
	strcpy(a[0].Name,"Cua rang me");          a[0].Price = 200000;
	strcpy(a[1].Name,"Chip chip hap");        a[1].Price = 150000;
	strcpy(a[2].Name,"Tom nuong muoi ot");    a[2].Price = 150000;
	strcpy(a[3].Name,"Lau ca mu");            a[3].Price = 150000;
	strcpy(a[4].Name,"Lau hai san");          a[4].Price = 150000;
	strcpy(a[5].Name,"Mi xao hai san");       a[5].Price = 200000;
	strcpy(a[6].Name,"Com chien hai san");    a[6].Price = 150000;
	strcpy(a[7].Name,"Tom hum nuong");        a[7].Price = 999999;
	strcpy(a[8].Name,"Bia heiniken");               a[8].Price = 35000;
	strcpy(a[9].Name,"Vodka");             a[9].Price = 100000;
	strcpy(a[10].Name,"Smothie");         a[10].Price = 30000;

	Gioithieu();
	getch();
	do{
		system("cls");
		magiaodich = NhapMagiaodich(magiaodich);
		system("cls");
		A : printMenu(a);
		Tong=0, discout=0;
		printf("-Ma don hang: %d\n", madonhang);
		ChonMon(luachon, dem);
		printLuaChon(a, luachon, dongia, dem, Tong);
		TinhTien(Tong, discout);
		ghiFile(file, a, luachon, dongia, dem, Tong, discout, madonhang, magiaodich);
		system("pause>nul");
		printf("\n---------------------------------------------------");
	 	printf("\n===============Nhap lua chon cua ban===============\nNhap  1 -> Tiep tuc\nNhap  0 -> Ket thuc ngay\n");
		do {
		end = KtraSoNguyen();
		madonhang++;
		if(end == 0){
			system("cls");
			Maketthucngay();
		}
		else if(end==1){
			system("cls");
			goto A;
		} 
		} while(end != 0 && end != 1 && end !=2);
	} while(end);
	system("cls");

	printf("\n\n\n\t\t\t\t====================Hen gap lai!====================");
	system("pause>nul");
}
