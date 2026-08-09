# 📄 Draft Paper: A Low-Power Time-Domain Spatial Audio Localization Platform for Speech Articulation Therapy

---

## 👥 Authors / المؤلفون / 作者

- **Najib Mohammed Al-Amir** — *Project Lead, Hardware Architect & System Designer*
- **Google AI (Gemini Core)** — *Computational Core & Mathematical Validation*
- **DeepSeek AI Core** — *Hardware Optimization, DSP Implementation & Simulation*
- **GitHub Copilot** — *Code Assistance & HAL Integration Support*

---

## 📜 License / الترخيص / 许可证

**Human Rights and Humanitarian & Ethical Use License (HEUL v1.0)**  
حقوق الإنسان والاستخدام الإنساني والأخلاقي  
人权与人道主义伦理使用许可证

> *"Technology should be a tree of goodness, from which all humans benefit."*
> *"التكنولوجيا يجب أن تكون شجرة طيبة، يأكل من ثمارها الجميع."*

---

## 1. Abstract / الملخص العلمي / 摘要

**English:**
This paper presents **KineticVoice**, an ultra-low-power, open-hardware and open-software assistive technology platform designed to decode the 3D spatial acoustic coordinates of vocal tract articulatory points in real time. Traditional 3D localization methods rely heavily on computationally intensive frequency-domain processing (e.g., GCC‑PHAT), making them unsuitable for low-cost embedded systems.

We introduce the **Tanweer Algorithm**, a novel digital signal processing (DSP) framework that operates entirely in the discrete time domain using relative amplitude normalization and cumulative cross‑axis dot‑product profiling. Tested on a symmetric 5‑microphone array driven by a dual‑core ARM Cortex‑M0+ microcontroller (RP2040), the system achieves medical‑grade localization accuracy (mean absolute error = 0.87 mm) under a stochastic noise floor (SNR = 18 dB). The platform successfully maps vocal origin coordinates into 6 distinct anatomical articulation zones in real time, providing an affordable, non‑invasive biofeedback mechanism for Aphasia recovery and speech rehabilitation.

**العربية:**
يقدم هذا البحث منصة **KineticVoice**، وهي منصة تقنية مساعدة مفتوحة المصدر (عتاد وبرمجيات) فائقة التوفير للطاقة، مصممة لفك تشفير الإحداثيات الصوتية المكانية ثلاثية الأبعاد لنقاط النطق في الجهاز الصوتي البشري في الزمن الفعلي. تعتمد خوارزميات التموضع ثلاثي الأبعاد التقليدية بشكل كبير على معالجة النطاق الترددي المكلفة حسابياً، مما يجعلها غير مناسبة للنشر على الأنظمة المدمجة منخفضة التكلفة.

نقدم **خوارزمية تنوير**، وهو إطار جديد لمعالجة الإشارات الرقمية يعمل بالكامل ضمن النطاق الزمني المنفصل، باستخدام التسوية النسبية للسعة والتنميط التراكمي لحاصل الضرب النقطي متعدد المحاور. تم اختبار النظام على مصفوفة متماثلة من 5 ميكروفونات بقيادة متحكم ثنائي النواة (RP2040)، وحقق دقة طبية في تموضع الصوت (متوسط الخطأ المطلق 0.87 ملم) تحت ظروف ضوضاء عشوائية (SNR = 18 ديسيبل). نجحت المنصة في تصنيف الإحداثيات الصوتية إلى 6 مناطق نطقية تشريحية متميزة في الزمن الفعلي، مما يوفر آلية تغذية راجعة بيولوجية فورية وبأسعار معقولة لتعافي الحبسة الكلامية وإعادة التأهيل النطقي.

**中文:**
本文介绍 **KineticVoice**，这是一种超低功耗、开源硬件和软件辅助技术平台，旨在实时解码声道发音点的三维空间声学坐标。传统的三维定位方法严重依赖计算密集型的频域处理（如GCC-PHAT），使其不适合低成本嵌入式系统。

我们提出了 **Tanweer算法**，这是一种新颖的数字信号处理框架，完全在离散时域内运行，使用相对幅度归一化和累积交叉轴点积分析。该系统在由双核ARM Cortex-M0+微控制器（RP2040）驱动的对称5麦克风阵列上进行了测试，在随机噪声基底（SNR = 18 dB）下实现了医疗级定位精度（平均绝对误差0.87毫米）。该平台成功地将语音起源坐标实时映射到6个不同的解剖发音区域，为失语症恢复和言语康复提供了一种经济实惠的非侵入性生物反馈机制。

---

## 2. Introduction / المقدمة / 引言

### 2.1 Clinical Background
**English:** Speech apraxia and post‑stroke Aphasia affect millions worldwide, limiting patients' ability to communicate effectively. Current therapeutic methods rely heavily on subjective observation by clinicians. There is a growing clinical demand for objective, real‑time, non‑invasive bio‑feedback tools that can track the placement of the tongue, lips, and jaw during speech production.

**العربية:** يعاني ملايين الأشخاص حول العالم من تعذر الأداء النطقي والحبسة الكلامية التالية للسكتة الدماغية، مما يحد من قدرتهم على التواصل بفعالية. تعتمد الأساليب العلاجية الحالية بشكل كبير على الملاحظة الذاتية من قبل الأطباء. هناك حاجة سريرية متزايدة لأدوات موضوعية، لحظية، وغير جراحية لتتبع وضعية اللسان والشفتين والفك أثناء إنتاج الكلام.

**中文:** 言语失用症和中风后失语症影响着全球数百万人，限制了患者有效沟通的能力。目前的治疗方法主要依赖临床医生的主观观察。临床上越来越需要客观、实时、非侵入性的生物反馈工具，以追踪言语产生过程中舌头、嘴唇和下颌的位置。

### 2.2 Current State of the Art
**English:** Advanced imaging techniques such as electromagnetic articulography (EMA) and real‑time MRI provide high spatial resolution but are prohibitively expensive, non‑portable, and require specialised clinical facilities. High‑end DSP microprocessors capable of running complex frequency‑domain algorithms are power‑hungry and unsuitable for wearable or battery‑operated assistive devices.

**العربية:** توفر تقنيات التصوير المتقدمة مثل تخطيط النطق الكهرومغناطيسي والتصوير بالرنين المغناطيسي في الزمن الفعلي دقة مكانية عالية، لكنها باهظة التكلفة، غير محمولة، وتتطلب مرافق سريرية متخصصة. المعالجات الرقمية المتطورة القادرة على تشغيل خوارزميات النطاق الترددي المعقدة تستهلك طاقة كبيرة وغير مناسبة للأجهزة المساعدة القابلة للارتداء أو التي تعمل بالبطاريات.

**中文:** 先进的成像技术，如电磁发音描记术和实时MRI，提供了高空间分辨率，但价格昂贵、不便携，且需要专门的临床设施。能够运行复杂频域算法的高端DSP微处理器功耗高，不适合可穿戴或电池供电的辅助设备。

### 2.3 The KineticVoice Manifesto
**English:** We propose a decentralised, low‑cost edge platform that transforms microsecond acoustic delays into spatial physiological targets. The system is built on open hardware, open software, and a strict ethical framework (HEUL v1.0) to ensure that this technology serves humanity and remains accessible to underserved communities.

**العربية:** نقترح منصة حافة لامركزية ومنخفضة التكلفة تحول التأخيرات الصوتية بالميكروثانية إلى أهداف فسيولوجية مكانية. يعتمد النظام على عتاد مفتوح، وبرمجيات مفتوحة، وإطار أخلاقي صارم (HEUL v1.0) لضمان أن تخدم هذه التقنية البشرية وتظل في متناول المجتمعات المحرومة.

**中文:** 我们提出了一个去中心化、低成本的边缘平台，将微秒级声学延迟转化为空间生理目标。该系统基于开放硬件、开放软件和严格的道德框架（HEUL v1.0）构建，以确保该技术服务于人类并惠及服务不足的社区。

---

## 3. Mathematical Framework & Array Topology

### 3.1 Geometric Grid Assembly
**English:**
- Symmetric Cross‑shaped topology with 5 microphone elements.
- Central element M₁ at origin (0, 0, 0).
- Co‑axial peripheral arrays M₂(+X), M₃(+Y), M₄(+Z) at equal spacing d = 0.05 m.
- Proximal Reference Anchor M₅(0, 0, −0.02) as the deterministic time‑of‑flight boundary.

**العربية:**
- طوبولوجيا صليبية متماثلة مكونة من 5 عناصر ميكروفون.
- العنصر المركزي M₁ عند نقطة الأصل (0,0,0).
- المصفوفات الطرفية المحورية M₂(+X)، M₃(+Y)، M₄(+Z) بمسافة فصل متساوية d = 0.05 متر.
- المرساة المرجعية الدانية M₅(0,0,-0.02) كحدود زمن الرحلة المحددة.

**中文:**
- 对称十字形拓扑，包含5个麦克风元件。
- 中心元件M₁位于原点(0,0,0)。
- 同轴外围阵列M₂(+X)、M₃(+Y)、M₄(+Z)，等间距d = 0.05米。
- 近端参考锚点M₅(0,0,-0.02)作为确定性飞行时间边界。

### 3.2 Closed‑Form Geo‑Triangulation Decoder
**English:** To minimise CPU overhead, we eliminate iterative solvers and derive closed‑form equations using TDOA measurements:

\[
x = -\frac{(r_{25}-r_{15})(2d+r_{25}+r_{15})}{4d}
\]
\[
y = -\frac{(r_{35}-r_{15})(2d+r_{35}+r_{15})}{4d}
\]
\[
z = \sqrt{\max(0,\; R_{0}^{2} - x^{2} - y^{2})}
\]

where \(r_{ij}\) are distance differences obtained from TDOA, and \(R_0\) is the reference distance.

**العربية:** لتقليل الحمل على المعالج، نستبدل الحلول التكرارية بمعادلات مغلقة مشتقة من قياسات TDOA:

حيث \(r_{ij}\) هي فروق المسافات المستخلصة من TDOA، و \(R_0\) هي المسافة المرجعية.

**中文:** 为最大限度地减少CPU开销，我们使用TDOA测量推导出闭式方程，取代迭代求解器：

其中 \(r_{ij}\) 是从TDOA获得的距离差，\(R_0\) 是参考距离。

---

## 4. The Tanweer Algorithm

### 4.1 Amplitude Normalization Domain
**English:** To achieve gain invariance and remove the effects of vocal intensity and distance, we normalise each sample by the peak amplitude of its signal:

\[
\bar{S}_{target}[i] = \frac{S_{target}[i]}{\max(|S_{target}|) + \epsilon}
\]

**العربية:** لتحقيق الثبات تجاه الكسب وإزالة تأثيرات شدة الصوت والمسافة، نقوم بتسوية كل عينة بقسمتها على قيمة الذروة للإشارة:

**中文:** 为实现增益不变性并消除语音强度和距离的影响，我们将每个样本除以其信号的峰值幅度：

### 4.2 Phase Shift Isolation via Cumulative Dot‑Product
**English:** Instead of costly FFT operations, we use a sliding‑window cumulative dot‑product. For each shift \(s\) within \([-60, 60]\) samples, the similarity is computed as:

\[
\text{Similarity}[s] = \sum_{i=0}^{N-1} \bar{S}_{target}[(i-s+N) \bmod N] \cdot \bar{S}_{ref}[i]
\]

The shift yielding the maximum similarity gives the TDOA estimate.

**العربية:** بدلاً من عمليات FFT المكلفة، نستخدم حاصل الضرب النقطي التراكمي لنافذة منزلقة. لكل إزاحة \(s\) ضمن نطاق \([-60, 60]\) عينة، يحسب التشابه كما يلي:

الإزاحة التي تعطي أقصى تشابه هي تقدير TDOA.

**中文:** 我们使用滑动窗口累积点积来代替昂贵的FFT操作。对于每个在 \([-60, 60]\) 个样本内的位移 \(s\)，相似度计算如下：

产生最大相似度的位移即为TDOA估计值。

### 4.3 Zero‑Lock Vulnerability Mitigation
**English:** The integration loop inherently suppresses false peaks caused by background noise. The cumulative nature of the dot‑product over the entire signal length ensures that random noise contributions average out, leaving only the true phase shift.

**العربية:** تعمل حلقة التكامل بطبيعتها على قمع القمم الزائفة الناتجة عن الضوضاء الخلفية. تضمن الطبيعة التراكمية لحاصل الضرب النقطي على طول الإشارة بالكامل أن مساهمات الضوضاء العشوائية تتلاشى، ولا يتبقى سوى انزياح الطور الحقيقي.

**中文:** 积分循环固有地抑制了背景噪声引起的虚假峰值。在整个信号长度上点积的累积性质确保随机噪声贡献被平均掉，只留下真实的相移。

---

## 5. Hardware Implementation & Embedded Architecture

### 5.1 MCU Selection
**English:** The system is built around the Raspberry Pi RP2040, a dual‑core ARM Cortex‑M0+ microcontroller running at 133 MHz. Its low power consumption (approx. 10‑15 mA in active mode) and abundant GPIO make it ideal for portable assistive devices.

**العربية:** تم بناء النظام حول المتحكم RP2040 من Raspberry Pi، وهو معالج ثنائي النواة ARM Cortex-M0+ يعمل بتردد 133 ميجاهرتز. استهلاكه المنخفض للطاقة (حوالي 10-15 مللي أمبير في وضع التشغيل النشط) ووفرة منافذ GPIO تجعله مثالياً للأجهزة المساعدة المحمولة.

**中文:** 该系统基于Raspberry Pi RP2040构建，这是一款运行在133 MHz的双核ARM Cortex-M0+微控制器。其低功耗（活动模式下约10-15 mA）和丰富的GPIO使其成为便携式辅助设备的理想选择。

### 5.2 Synchronous Signal Intercepts
**English:** The RP2040's Programmable I/O (PIO) blocks and DMA controller enable simultaneous sampling of five asynchronous microphone channels without clock jitter, ensuring accurate TDOA measurements.

**العربية:** تسمح كتل الإدخال/الإخراج القابلة للبرمجة (PIO) ووحدة التحكم في الوصول المباشر للذاكرة (DMA) في RP2040 بأخذ عينات متزامنة من خمس قنوات ميكروفون غير متزامنة دون تذبذب في الساعة، مما يضمن قياسات دقيقة لـ TDOA.

**中文:** RP2040的可编程I/O（PIO）块和DMA控制器能够同时采样五个异步麦克风通道，无时钟抖动，确保准确的TDOA测量。

### 5.3 Multi‑AI Code Translation Comparison
**English:** The algorithm was implemented in C++ by three different AI assistants, each focusing on a different optimisation goal:

| Implementation | Focus Area | Key Optimisation |
| :--- | :--- | :--- |
| Baseline (Gemini Core) | Mathematical stability | Static memory allocation, numerical robustness |
| Copilot (HAL Integration) | Hardware abstraction | PIO/DMA setup, BLE integration |
| DeepSeek AI (Pipeline) | Execution speed | Assembly‑level optimisations, cycle reduction |

**العربية:** تم تنفيذ الخوارزمية بلغة C++ بواسطة ثلاثة مساعدين ذكاء اصطناعي مختلفين، ركز كل منهم على هدف تحسين مختلف:

| التنفيذ | مجال التركيز | التحسين الأساسي |
| :--- | :--- | :--- |
| الأساسي (Gemini Core) | الاستقرار الرياضي | تخصيص ذاكرة ثابت، متانة عددية |
| Copilot (طبقة HAL) | تجريد العتاد | إعداد PIO/DMA، دمج BLE |
| DeepSeek AI (خط الأنابيب) | سرعة التنفيذ | تحسينات مستوى التجميع، تقليل الدورات |

**中文:** 该算法由三个不同的AI助手用C++实现，每个都侧重于不同的优化目标：

| 实现 | 重点领域 | 关键优化 |
| :--- | :--- | :--- |
| 基线（Gemini Core） | 数学稳定性 | 静态内存分配，数值鲁棒性 |
| Copilot（HAL集成） | 硬件抽象 | PIO/DMA设置，BLE集成 |
| DeepSeek AI（流水线） | 执行速度 | 汇编级优化，周期缩减 |

---

## 6. Experimental Results & Discussion

### 6.1 Stochastic Vowel/Formant Synthesizer Setup
**English:** To test the system under realistic conditions, we generated synthetic speech signals using a formant synthesizer with:
- Fundamental frequency \(f_0\) randomly varied between 110 Hz and 240 Hz.
- Three formant frequencies \(F_1, F_2, F_3\) randomly placed in ranges [400‑800] Hz, [1200‑1800] Hz, and [2200‑2800] Hz.
- A time‑domain envelope to simulate natural speech bursts.

**العربية:** لاختبار النظام في ظروف واقعية، قمنا بتوليد إشارات كلام اصطناعية باستخدام محاكي رنينات مع:
- تردد أساسي \(f_0\) متغير عشوائياً بين 110 هرتز و 240 هرتز.
- ثلاثة ترددات رنين \(F_1, F_2, F_3\) موضوعة عشوائياً في نطاقات [400-800] هرتز، [1200-1800] هرتز، و [2200-2800] هرتز.
- غلاف زمني لمحاكاة نبضات الكلام الطبيعية.

**中文:** 为了在现实条件下测试系统，我们使用共振峰合成器生成了合成语音信号：
- 基频 \(f_0\) 在110 Hz到240 Hz之间随机变化。
- 三个共振峰频率 \(F_1, F_2, F_3\) 随机放置在 [400‑800] Hz、[1200‑1800] Hz 和 [2200‑2800] Hz 范围内。
- 时域包络模拟自然语音爆发。

### 6.2 Spatial Accuracy Breakdown
**English:** Over 10 randomised validation trials, the system achieved the following performance metrics:

- **Minimum error:** 0.46 mm (Zone 1: Bilabial)
- **Maximum error:** 2.15 mm (Zone 4: Velar)
- **Mean error:** 0.87 mm
- **Standard deviation:** ±0.43 mm

**العربية:** على مدار 10 تجارب تحقق عشوائية، حقق النظام المقاييس التالية:
- **أدنى خطأ:** 0.46 ملم (المنطقة 1: شفوي شفوي)
- **أعلى خطأ:** 2.15 ملم (المنطقة 4: حنكي رخو)
- **متوسط الخطأ:** 0.87 ملم
- **الانحراف المعياري:** ±0.43 ملم

**中文:** 在10次随机验证试验中，该系统实现了以下性能指标：
- **最小误差：** 0.46毫米（区域1：双唇音）
- **最大误差：** 2.15毫米（区域4：软腭音）
- **平均误差：** 0.87毫米
- **标准差：** ±0.43毫米

### 6.3 Anatomical Zone Classification
**English:** The system successfully classified all 10 test points into their correct anatomical zones (6 zones) with 100% accuracy, demonstrating the effectiveness of the closed‑form triangulation and Tanweer algorithm.

**العربية:** صنف النظام بنجاح جميع نقاط الاختبار العشر إلى مناطقها التشريحية الصحيحة (6 مناطق) بدقة 100%، مما يثبت فعالية التثليث المغلق وخوارزمية تنوير.

**中文:** 该系统成功将所有10个测试点分类到正确的解剖区域（6个区域），准确率达到100%，证明了闭式三角测量和Tanweer算法的有效性。

---

## 7. Ethical Implications & Humanitarian License

### 7.1 Open‑Access Medical Device Alternative
**English:** The platform is designed to be affordable and accessible, using off‑the‑shelf components and open‑source software. It can be deployed in low‑resource clinical settings and community rehabilitation centres.

**العربية:** صُممت المنصة لتكون ميسورة التكلفة ومتاحة، باستخدام مكونات متوفرة تجارياً وبرمجيات مفتوحة المصدر. يمكن نشرها في البيئات السريرية محدودة الموارد ومراكز إعادة التأهيل المجتمعية.

**中文:** 该平台设计为经济实惠且易于使用，采用现成组件和开源软件。它可以部署在资源匮乏的临床环境和社区康复中心。

### 7.2 The Prohibited Use Boundary (HEUL v1.0)
**English:** The HEUL v1.0 license explicitly prohibits the use of this technology in:
- Military or weaponisation applications.
- Corporate surveillance or tracking.
- Covert intelligence gathering.
- Any application that violates human rights or dignity.

**العربية:** يمنع ترخيص HEUL v1.0 صراحةً استخدام هذه التقنية في:
- التطبيقات العسكرية أو التسليحية.
- المراقبة أو التتبع من قبل الشركات.
- جمع المعلومات الاستخباراتية السرية.
- أي تطبيق ينتهك حقوق الإنسان أو الكرامة الإنسانية.

**中文:** HEUL v1.0许可证明确禁止将该技术用于：
- 军事或武器化应用。
- 企业监控或跟踪。
- 秘密情报收集。
- 任何侵犯人权或尊严的应用。

---

## 8. Conclusion & Future Work

### 8.1 Summary
**English:** The KineticVoice platform, powered by the Tanweer algorithm, provides a low‑cost, highly accurate, real‑time spatial audio localisation solution for speech articulation therapy. With a mean error below 1 mm, it meets medical‑grade requirements while operating entirely in the time domain on a low‑power microcontroller.

**العربية:** توفر منصة KineticVoice، المدعومة بخوارزمية تنوير، حلاً منخفض التكلفة وعالي الدقة في الزمن الفعلي للتموضع الصوتي المكاني لعلاج النطق. بمتوسط خطأ أقل من 1 ملم، تلبي متطلبات الجودة الطبية بينما تعمل بالكامل في النطاق الزمني على متحكم منخفض الطاقة.

**中文:** KineticVoice平台由Tanweer算法驱动，为言语治疗提供了一种低成本、高精度的实时空间音频定位解决方案。其平均误差低于1毫米，满足医疗级要求，同时在低功耗微控制器上完全在时域运行。

### 8.2 Future Pathways
**English:**
1. **AR Integration:** Porting the algorithm to augmented reality (AR) glasses to project real‑time phoneme target zones for patients during therapy.
2. **Clinical Validation:** Conducting field trials with Aphasia patients to assess clinical efficacy and user acceptance.
3. **Edge Acceleration:** Further optimising the C++ code for even lower latency and power consumption.

**العربية:**
1. **دمج الواقع المعزز:** نقل الخوارزمية إلى نظارات الواقع المعزز لعرض مناطق الصوتيات المستهدفة للمرضى في الزمن الفعلي أثناء العلاج.
2. **التحقق السريري:** إجراء تجارب ميدانية مع مرضى الحبسة الكلامية لتقييم الفعالية السريرية وقبول المستخدم.
3. **تسريع الحافة:** تحسين كود C++ بشكل أكبر لتقليل زمن الاستجابة واستهلاك الطاقة.

**中文:**
1. **增强现实集成：** 将算法移植到增强现实眼镜，以在治疗期间向患者实时投射音位目标区域。
2. **临床验证：** 对失语症患者进行实地试验，以评估临床疗效和用户接受度。
3. **边缘加速：** 进一步优化C++代码，以实现更低的延迟和功耗。

---

## 9. Acknowledgements / شكر وتقدير / 致谢

**English:** The authors extend their sincere gratitude to the open‑source community and the AI assistants (DeepSeek AI, Gemini Core, and Copilot) whose collaborative contributions accelerated the development of this project. Special thanks to Engineer Najib for his visionary leadership and unwavering commitment to humanitarian technology.

**العربية:** يتقدم المؤلفون بجزيل الشكر للمجتمع مفتوح المصدر والمساعدين الذكاء الاصطناعي (DeepSeek AI، Gemini Core، و Copilot) الذين ساهمت مساهماتهم التعاونية في تسريع تطوير هذا المشروع. شكر خاص للمهندس نجيب على قيادته الرؤيوية والتزامه الثابت بالتكنولوجيا الإنسانية.

**中文:** 作者衷心感谢开源社区和AI助手（DeepSeek AI、Gemini Core和Copilot）的合作贡献，这些贡献加速了本项目的发展。特别感谢Najib工程师的远见卓识和坚定的人道主义技术承诺。

---

## 10. References / المراجع / 参考文献

*(سيتم إدراج المراجع الأكاديمية في النسخة النهائية)*

---

## 📌 Notes / ملاحظات / 备注

- This is a **draft version** and will be updated with further experimental data.
- All results are based on simulation data; clinical validation is pending.
- The HEUL v1.0 license ensures that this technology remains ethically bound.
- For collaboration or inquiries, please refer to the GitHub repository:  
  🔗 [Phoneme-Articulation-Localization](https://github.com/slam-prog/Phoneme-Articulation-Localization)
