## Adım 0 – Ön Gereksinimler

Bu klasör, SQLAlchemy öğrenimine başlamadan önce tamamlanması önerilen **veri tabanı ve SQL ön gereksinimlerini** içerir.  
Amaç, hiç veri tabanı bilmeyen bir okuyucuyu, ilişkisel veri tabanı kavramlarını ve temel SQL komutlarını anlayacak seviyeye getirmek ve SQLAlchemy dokümanlarını rahatça takip edebilecek zihinsel altyapıyı oluşturmaktır.

---

### Hedef Kitle

- Veri tabanı ve SQL konusunda başlangıç seviyesinde olan geliştiriciler  
- Python ile SQLAlchemy kullanmak isteyen, ancak veri tabanı temellerini gözden geçirmek isteyenler  
- Kurumsal düzeyde ilişkisel veri tabanı mantığını ve terimlerini sistematik öğrenmek isteyenler  

---

### Öğrenme Çıktıları

Bu klasördeki içerikleri tamamlayan bir okuyucunun aşağıdaki başlıklarda temel düzeyde yetkinlik kazanması hedeflenir:

- Veri, bilgi, veri tabanı ve ilişkisel veri tabanı kavramlarını açıklayabilmek  
- Tablo, satır, sütun, primary key ve foreign key kavramlarını doğru kullanmak  
- Temel SQL CRUD komutlarını (SELECT, INSERT, UPDATE, DELETE) yazabilmek  
- Filtreleme, sıralama, gruplama ve basit JOIN işlemlerini uygulayabilmek  
- İlişki türlerini (One-to-One, One-to-Many, Many-to-Many) gerçek örneklerle bağdaştırabilmek  
- Normalizasyon, index ve transaction kavramlarının ne işe yaradığını ifade edebilmek  
- SQL tarafındaki bu kavramları, SQLAlchemy ORM dünyasındaki `Column`, `relationship`, `ForeignKey`, `index`, `session.commit()` gibi yapılara zihinsel olarak eşleyebilmek  

---

### Dosya Yapısı ve Önerilen Okuma Sırası

**Genel bakış ve seviye kontrolü**

- `0.0 Ön Gereksinimler Genel Bakış.md`  
  - Klasördeki tüm başlıkların özeti, önerilen okuma sırası ve genel yol haritası.  
- `Ön Gereksinimler Seviye Değerlendirme.md`  
  - Tüm içeriği tamamladıktan sonra kendi seviyenizi kontrol edebileceğiniz soru ve checklist.  

**1.x – Kavramsal temel**

- `1.1 Veri Nedir.md`  
  - Veri ve bilgi arasındaki fark, yapısal/yapısal olmayan veri, veriyi düzenleme ihtiyacı.  
- `1.2 Veritabanı Nedir.md`  
  - Veri tabanı tanımı, Excel ile farklar, kurumsal sistemlerde veri tabanının rolü.  
- `1.3 İlişkisel Veritabanı(RDBMS) Nedir.md`  
  - Tablo, satır, sütun kavramları, tabloları ayırma fikri, ilişkisel modelin temeli.  
- `1.4 Primary Key Nedir.md`  
  - Kayıtların benzersiz tanımlanması, doğal/yapay anahtar, diğer tablolar için referans noktası.  

**2.x – SQL temelleri ve şema tasarımı**

- `2.1 SQL Temelleri.md`  
  - SELECT komutunun yapısı, sütun seçimi, WHERE ile filtreleme, temel sorgu mantığı.  
- `2.2 Temel Veritabanı Komutları.md`  
  - SELECT, INSERT, UPDATE, DELETE, ORDER BY, LIMIT, COUNT/SUM/AVG, GROUP BY ve temel JOIN kullanımı.  
- `2.3 İlişkisel Veri Modelleri.md`  
  - E-ticaret/benzeri senaryolar üzerinden varlık–ilişki modelleme, tablo tasarımı, temel sorgu örnekleri.  
- `2.4 Veri Tipleri, Kısıtlamalar ve NULL.md`  
  - Temel veri tipleri, NOT NULL/UNIQUE/PRIMARY KEY/FOREIGN KEY/DEFAULT/CHECK, NULL mantığı ve SQLAlchemy karşılıkları.  
- `2.5 CREATE TABLE ile Şema Tasarımı.md`  
  - Tam `CREATE TABLE` örnekleri ile veri tipi ve kısıtlamaların tablo tanımı içinde birleştirilmesi.  
- `2.6 JOIN Türlerine Giriş.md`  
  - INNER JOIN ve LEFT JOIN’in kavramsal farkı, sade senaryolarla uygulama.  

**3.x – İlişkiler, normalizasyon, performans ve güvenlik**

- `3.1 Foreign Key Nedir.md`  
  - Foreign key tanımı, primary key ile ilişkisi, veri bütünlüğü açısından rolü ve SQL/SQLAlchemy örnekleri.  
- `3.2 Veritabanında İlişki Türleri.md`  
  - One-to-One, One-to-Many, Many-to-Many ilişki tipleri; foreign key konumları ve ara tablolar.  
- `3.3 Normalizasyon Nedir.md`  
  - Veri tekrarını azaltma, yanlış/doğru tasarım karşılaştırmaları, 1NF–2NF–3NF’e sezgisel bakış.  
- `3.4 Index Nedir.md`  
  - Index kavramı, full table scan ile farkı, hangi sütunlara index konulacağı ve maliyet/fayda dengesi.  
- `3.5 Transaction Nedir.md`  
  - Transaction akışı (BEGIN/COMMIT/ROLLBACK), ACID özelliklerine giriş ve gerçek sistem senaryoları.  

---

### Bu Klasör Nasıl Kullanılmalı?

- İçerik, tamamen sıfırdan başlayan bir okuyucuyu gözeterek **kademeli ve kavramsal** bir akışla tasarlanmıştır.  
- Dosyalar mümkün olduğunca sırayla okunmalı; özellikle 1.x ve 2.x tamamlanmadan 3.x’e geçilmemesi önerilir.  
- Her dosyanın sonunda yer alan küçük alıştırma ve düşünme soruları, kavramların pekişmesi için tasarlanmıştır.  
- Tüm dosyalar tamamlandıktan sonra `Ön Gereksinimler Seviye Değerlendirme.md` içindeki sorular üzerinden kendi seviyenizi değerlendirebilirsiniz.  

Bu klasör, SQLAlchemy notlarının geri kalanında sıkça atıf yapılacak temel terminoloji ve kavramları toplu hâlde sunar. Bu aşamayı tamamlayan bir okuyucu, SQLAlchemy ORM kullanımına geçmek için gerekli ön bilgi setine sahip kabul edilir.

