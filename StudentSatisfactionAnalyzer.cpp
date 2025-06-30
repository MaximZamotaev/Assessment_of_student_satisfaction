#pragma setlocale(".1251")
#pragma execution_character_set("utf-8")

// Add external linkage for C++ functions
#ifdef __cplusplus
extern "C" {
#endif

#include "MLMethods.h"

#ifdef __cplusplus
}
#endif

#ifdef _MANAGED
#pragma managed(push, on)

#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Text;

public ref class MainForm : public Form
{
private:
    // UI Elements
    Label^ titleLabel;
    Label^ instructionsLabel1;
    Label^ instructionsLabel2;
    Label^ instructionsLabel3;
    Label^ instructionsLabel4;
    array<TextBox^>^ factorInputs;
    array<Label^>^ factorLabels;
    Button^ boostedTreesButton;
    Button^ randomForestButton;
    Button^ annButton;
    Button^ allMethodsButton;
    Button^ clearButton;
    Label^ satisfactionLabel;
    TextBox^ satisfactionOutput;

    // Additional UI elements for combined results
    Panel^ combinedResultsPanel;
    array<Label^>^ methodLabels;
    array<TextBox^>^ satisfactionOutputs;

    // Required designer variable
    System::ComponentModel::Container^ components;

    // Factor names
    array<String^>^ factorNames;

public:
    MainForm() {
        components = nullptr;
        // Initialize factorNames
        factorNames = gcnew array<String^> {
            L"Эмоциональное состояние",
                L"Психологическое состояние",
                L"Физическое состояние",
                L"Интеллектуальное состояние",
                L"Уверенность в себе",
                L"Восприятие мира",
                L"Лабораторные занятия",
                L"Лекционные занятия",
                L"Общение с сокурсниками",
                L"Общение с преподавателями",
                L"Досуг",
                L"Спорт",
                L"Научная работа",
                L"Стипендия",
                L"Транспортная доступность",
                L"Материально-техническая база",
                L"Программное обеспечение учебного процесса",
                L"Материальное состояние студента",
                L"Перспективы трудоустройства",
                L"Возможность совмещения работы с учёбой"
        };

        try {
            InitializeComponent();
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при инициализации формы: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            Application::Exit();
        }
    }

protected:
    ~MainForm() {
        if (components) {
            delete components;
        }

        if (factorInputs) {
            for (int i = 0; i < factorInputs->Length; i++) {
                if (factorInputs[i]) delete factorInputs[i];
            }
            delete factorInputs;
        }
        if (factorLabels) {
            for (int i = 0; i < factorLabels->Length; i++) {
                if (factorLabels[i]) delete factorLabels[i];
            }
            delete factorLabels;
        }
        if (methodLabels) {
            for (int i = 0; i < methodLabels->Length; i++) {
                if (methodLabels[i]) delete methodLabels[i];
            }
            delete methodLabels;
        }
        if (satisfactionOutputs) {
            for (int i = 0; i < satisfactionOutputs->Length; i++) {
                if (satisfactionOutputs[i]) delete satisfactionOutputs[i];
            }
            delete satisfactionOutputs;
        }
        if (titleLabel) delete titleLabel;
        if (instructionsLabel1) delete instructionsLabel1;
        if (instructionsLabel2) delete instructionsLabel2;
        if (instructionsLabel3) delete instructionsLabel3;
        if (instructionsLabel4) delete instructionsLabel4;
        if (boostedTreesButton) delete boostedTreesButton;
        if (randomForestButton) delete randomForestButton;
        if (annButton) delete annButton;
        if (allMethodsButton) delete allMethodsButton;
        if (clearButton) delete clearButton;
        if (satisfactionLabel) delete satisfactionLabel;
        if (satisfactionOutput) delete satisfactionOutput;
        if (combinedResultsPanel) delete combinedResultsPanel;
    }

private:
    void InitializeComponent() {
        // Form settings with coral color scheme
        this->Text = L"Оценка уровня удовлетворённости студентов";
        this->Size = Drawing::Size(1200, 750);
        this->StartPosition = FormStartPosition::CenterScreen;
        this->BackColor = Color::FromArgb(255, 242, 237);

        // Create title label
        titleLabel = gcnew Label();
        if (!titleLabel) throw gcnew Exception(L"Не удалось создать titleLabel");
        titleLabel->Text = L"Оценка уровня удовлетворённости студентов обучением в высшем учебном заведении";
        titleLabel->Font = gcnew Drawing::Font(titleLabel->Font->FontFamily, 16, FontStyle::Bold);
        titleLabel->Location = Point(110, 20);
        titleLabel->AutoSize = true;
        titleLabel->Size = Drawing::Size(1150, 40);
        titleLabel->TextAlign = ContentAlignment::MiddleCenter;
        titleLabel->ForeColor = Color::FromArgb(205, 92, 92);
        titleLabel->BackColor = Color::Transparent;
        this->Controls->Add(titleLabel);

        // Create GroupBox for factors section
        GroupBox^ factorsGroupBox = gcnew GroupBox();
        factorsGroupBox->Text = L"Оценка факторов";
        factorsGroupBox->Location = Point(10, 80);
        factorsGroupBox->Size = Drawing::Size(1160, 380);
        factorsGroupBox->Font = gcnew Drawing::Font(factorsGroupBox->Font->FontFamily, 12, FontStyle::Bold);
        factorsGroupBox->ForeColor = Color::FromArgb(205, 92, 92);
        factorsGroupBox->BackColor = Color::Transparent;
        this->Controls->Add(factorsGroupBox);

        // Create instructions label1
        instructionsLabel1 = gcnew Label();
        if (!instructionsLabel1) throw gcnew Exception(L"Не удалось создать instructionsLabel1");
        instructionsLabel1->Text = L"Оцените по шкале от 0 до 10 включительно каждый из 20 факторов, влияющих на ваш уровень удовлетворённости обучением в высшем учебном заведении:";
        instructionsLabel1->Font = gcnew Drawing::Font(instructionsLabel1->Font->FontFamily, 10.5, FontStyle::Bold);
        instructionsLabel1->Location = Point(10, 30);
        instructionsLabel1->Size = Drawing::Size(1140, 40);
        instructionsLabel1->ForeColor = Color::FromArgb(205, 92, 92);
        instructionsLabel1->BackColor = Color::Transparent;
        factorsGroupBox->Controls->Add(instructionsLabel1);

        // Create factor input boxes and labels
        factorInputs = gcnew array<TextBox^>(20);
        if (!factorInputs) throw gcnew Exception(L"Не удалось создать массив factorInputs");
        factorLabels = gcnew array<Label^>(20);
        if (!factorLabels) throw gcnew Exception(L"Не удалось создать массив factorLabels");

        int startX = 10;
        int startY = 90;
        int boxWidth = 71;
        int boxHeight = 21;
        int labelWidth = 200;
        int spacing = 30;
        int itemsPerRow = 4;

        for (int i = 0; i < 20; i++) {
            int row = i / itemsPerRow;
            int col = i % itemsPerRow;

            factorLabels[i] = gcnew Label();
            if (!factorLabels[i]) throw gcnew Exception(String::Format(L"Не удалось создать factorLabels[{0}]", i));
            factorLabels[i]->Text = factorNames[i];
            factorLabels[i]->Location = Point(startX + col * (labelWidth + boxWidth + 20),
                startY + row * (boxHeight + spacing));
            factorLabels[i]->Size = Drawing::Size(labelWidth * 1.05, boxHeight * 2.5);
            factorLabels[i]->Font = gcnew Drawing::Font(factorLabels[i]->Font->FontFamily, 10, FontStyle::Bold);
            factorLabels[i]->ForeColor = Color::Black;
            factorLabels[i]->BackColor = Color::Transparent;
            factorsGroupBox->Controls->Add(factorLabels[i]);

            factorInputs[i] = gcnew TextBox();
            if (!factorInputs[i]) throw gcnew Exception(String::Format(L"Не удалось создать factorInputs[{0}]", i));
            factorInputs[i]->Location = Point(startX + col * (labelWidth + boxWidth + 20) + labelWidth,
                startY + row * (boxHeight + spacing));
            factorInputs[i]->Size = Drawing::Size(boxWidth, boxHeight * 1.5);
            factorInputs[i]->TextAlign = HorizontalAlignment::Center;
            factorInputs[i]->TabIndex = i + 1;
            factorInputs[i]->BackColor = Color::White;
            factorInputs[i]->ForeColor = Color::Black;
            factorsGroupBox->Controls->Add(factorInputs[i]);
        }

        // Create GroupBox for method selection
        GroupBox^ methodsGroupBox = gcnew GroupBox();
        methodsGroupBox->Text = L"Выбор метода";
        methodsGroupBox->Location = Point(10, 470);
        methodsGroupBox->Size = Drawing::Size(520, 230);
        methodsGroupBox->Font = gcnew Drawing::Font(methodsGroupBox->Font->FontFamily, 12, FontStyle::Bold);
        methodsGroupBox->ForeColor = Color::FromArgb(205, 92, 92);
        methodsGroupBox->BackColor = Color::Transparent;
        this->Controls->Add(methodsGroupBox);

        // Create instructions label2
        instructionsLabel2 = gcnew Label();
        if (!instructionsLabel2) throw gcnew Exception(L"Не удалось создать instructionsLabel2");
        instructionsLabel2->Text = L"Выберите один из трёх методов машинного обучения:";
        instructionsLabel2->Font = gcnew Drawing::Font(instructionsLabel2->Font->FontFamily, 10, FontStyle::Bold);
        instructionsLabel2->Location = Point(60, 30);
        instructionsLabel2->Size = Drawing::Size(420, 20);
        instructionsLabel2->ForeColor = Color::FromArgb(205, 92, 92);
        instructionsLabel2->BackColor = Color::Transparent;
        methodsGroupBox->Controls->Add(instructionsLabel2);

        // Create method selection buttons
        boostedTreesButton = gcnew Button();
        if (!boostedTreesButton) throw gcnew Exception(L"Не удалось создать boostedTreesButton");
        boostedTreesButton->Text = L"Boosted Trees";
        boostedTreesButton->Location = Point(60, 55);
        boostedTreesButton->Size = Drawing::Size(200, 30);
        boostedTreesButton->Font = gcnew Drawing::Font(boostedTreesButton->Font->FontFamily, 9, FontStyle::Bold);
        boostedTreesButton->BackColor = Color::FromArgb(233, 150, 122);
        boostedTreesButton->ForeColor = Color::Black;
        boostedTreesButton->FlatStyle = FlatStyle::Flat;
        boostedTreesButton->Click += gcnew EventHandler(this, &MainForm::BoostedTreesButton_Click);
        methodsGroupBox->Controls->Add(boostedTreesButton);

        randomForestButton = gcnew Button();
        if (!randomForestButton) throw gcnew Exception(L"Не удалось создать randomForestButton");
        randomForestButton->Text = L"Random Forest";
        randomForestButton->Location = Point(280, 55);
        randomForestButton->Size = Drawing::Size(200, 30);
        randomForestButton->Font = gcnew Drawing::Font(randomForestButton->Font->FontFamily, 9, FontStyle::Bold);
        randomForestButton->BackColor = Color::FromArgb(233, 150, 122);
        randomForestButton->ForeColor = Color::Black;
        randomForestButton->FlatStyle = FlatStyle::Flat;
        randomForestButton->Click += gcnew EventHandler(this, &MainForm::RandomForestButton_Click);
        methodsGroupBox->Controls->Add(randomForestButton);

        annButton = gcnew Button();
        if (!annButton) throw gcnew Exception(L"Не удалось создать annButton");
        annButton->Text = L"Искусственная нейронная сеть (ANN) с архитектурой MLP 20-17-3";
        annButton->Location = Point(60, 95);
        annButton->Size = Drawing::Size(420, 40);
        annButton->Font = gcnew Drawing::Font(annButton->Font->FontFamily, 9, FontStyle::Bold);
        annButton->BackColor = Color::FromArgb(233, 150, 122);
        annButton->ForeColor = Color::Black;
        annButton->FlatStyle = FlatStyle::Flat;
        annButton->Click += gcnew EventHandler(this, &MainForm::ANNButton_Click);
        methodsGroupBox->Controls->Add(annButton);

        // Create instructions label3
        instructionsLabel3 = gcnew Label();
        if (!instructionsLabel3) throw gcnew Exception(L"Не удалось создать instructionsLabel3");
        instructionsLabel3->Text = L"Либо же вы можете выбрать все три метода сразу для проведения более комплексного анализа:";
        instructionsLabel3->Font = gcnew Drawing::Font(instructionsLabel3->Font->FontFamily, 10, FontStyle::Bold);
        instructionsLabel3->Location = Point(60, 145);
        instructionsLabel3->Size = Drawing::Size(420, 40);
        instructionsLabel3->ForeColor = Color::FromArgb(205, 92, 92);
        instructionsLabel3->BackColor = Color::Transparent;
        methodsGroupBox->Controls->Add(instructionsLabel3);

        allMethodsButton = gcnew Button();
        if (!allMethodsButton) throw gcnew Exception(L"Не удалось создать allMethodsButton");
        allMethodsButton->Text = L"Все три метода";
        allMethodsButton->Location = Point(60, 190);
        allMethodsButton->Size = Drawing::Size(420, 30);
        allMethodsButton->Font = gcnew Drawing::Font(allMethodsButton->Font->FontFamily, 9, FontStyle::Bold);
        allMethodsButton->BackColor = Color::FromArgb(233, 150, 122);
        allMethodsButton->ForeColor = Color::Black;
        allMethodsButton->FlatStyle = FlatStyle::Flat;
        allMethodsButton->Click += gcnew EventHandler(this, &MainForm::AllMethodsButton_Click);
        methodsGroupBox->Controls->Add(allMethodsButton);

        // Create satisfaction output
        satisfactionLabel = gcnew Label();
        if (!satisfactionLabel) throw gcnew Exception(L"Не удалось создать satisfactionLabel");
        satisfactionLabel->Text = L"Уровень удовлетворённости:";
        satisfactionLabel->Location = Point(550, 605);
        satisfactionLabel->AutoSize = true;
        satisfactionLabel->Font = gcnew Drawing::Font(satisfactionLabel->Font->FontFamily, 10, FontStyle::Bold);
        satisfactionLabel->ForeColor = Color::Black;
        satisfactionLabel->BackColor = Color::Transparent;
        this->Controls->Add(satisfactionLabel);

        satisfactionOutput = gcnew TextBox();
        if (!satisfactionOutput) throw gcnew Exception(L"Не удалось создать satisfactionOutput");
        satisfactionOutput->Location = Point(790, 605);
        satisfactionOutput->Size = Drawing::Size(310, 30);
        satisfactionOutput->TextAlign = HorizontalAlignment::Center;
        satisfactionOutput->Font = gcnew Drawing::Font(satisfactionOutput->Font->FontFamily, 10, FontStyle::Bold);
        satisfactionOutput->ReadOnly = true;
        satisfactionOutput->BackColor = Color::White;
        satisfactionOutput->ForeColor = Color::Black;
        this->Controls->Add(satisfactionOutput);

        // Create GroupBox for results
        GroupBox^ resultsGroupBox = gcnew GroupBox();
        resultsGroupBox->Text = L"Результаты";
        resultsGroupBox->Location = Point(540, 470);
        resultsGroupBox->Size = Drawing::Size(570, 230);
        resultsGroupBox->Font = gcnew Drawing::Font(resultsGroupBox->Font->FontFamily, 12, FontStyle::Bold);
        resultsGroupBox->ForeColor = Color::FromArgb(205, 92, 92);
        resultsGroupBox->BackColor = Color::Transparent;
        this->Controls->Add(resultsGroupBox);

        // Create combined results panel
        combinedResultsPanel = gcnew Panel();
        if (!combinedResultsPanel) throw gcnew Exception(L"Не удалось создать combinedResultsPanel");
        combinedResultsPanel->Location = Point(5, 30);
        combinedResultsPanel->Size = Drawing::Size(550, 140);
        combinedResultsPanel->Visible = false;
        combinedResultsPanel->BackColor = Color::Transparent;
        resultsGroupBox->Controls->Add(combinedResultsPanel);

        // Create arrays for combined results
        methodLabels = gcnew array<Label^>(3);
        if (!methodLabels) throw gcnew Exception(L"Не удалось создать массив methodLabels");
        satisfactionOutputs = gcnew array<TextBox^>(3);
        if (!satisfactionOutputs) throw gcnew Exception(L"Не удалось создать массив satisfactionOutputs");

        array<String^>^ methodNames = {
            L"Boosted Trees:",
            L"Random Forest:",
            L"Искусственная нейронная сеть (ANN) с архитектурой MLP 20-17-3:"
        };

        for (int i = 0; i < 3; i++) {
            methodLabels[i] = gcnew Label();
            if (!methodLabels[i]) throw gcnew Exception(String::Format(L"Не удалось создать methodLabels[{0}]", i));
            methodLabels[i]->Text = methodNames[i];
            methodLabels[i]->Location = Point(10, i * 50);
            methodLabels[i]->Size = Drawing::Size(300, 40);
            methodLabels[i]->Font = gcnew Drawing::Font(methodLabels[i]->Font->FontFamily, 10, FontStyle::Bold);
            methodLabels[i]->ForeColor = Color::Black;
            methodLabels[i]->BackColor = Color::Transparent;
            combinedResultsPanel->Controls->Add(methodLabels[i]);

            satisfactionOutputs[i] = gcnew TextBox();
            if (!satisfactionOutputs[i]) throw gcnew Exception(String::Format(L"Не удалось создать satisfactionOutputs[{0}]", i));
            satisfactionOutputs[i]->Location = Point(320, i * 50);
            satisfactionOutputs[i]->Size = Drawing::Size(220, 30);
            satisfactionOutputs[i]->TextAlign = HorizontalAlignment::Center;
            satisfactionOutputs[i]->Font = gcnew Drawing::Font(satisfactionOutputs[i]->Font->FontFamily, 10, FontStyle::Bold);
            satisfactionOutputs[i]->ReadOnly = true;
            satisfactionOutputs[i]->BackColor = Color::White;
            satisfactionOutputs[i]->ForeColor = Color::Black;
            combinedResultsPanel->Controls->Add(satisfactionOutputs[i]);
        }

        // Create clear button
        clearButton = gcnew Button();
        if (!clearButton) throw gcnew Exception(L"Не удалось создать clearButton");
        clearButton->Text = L"Очистить данные";
        clearButton->Location = Point(10, 190);
        clearButton->Size = Drawing::Size(550, 30);
        clearButton->Font = gcnew Drawing::Font(clearButton->Font->FontFamily, 10, FontStyle::Bold);
        clearButton->BackColor = Color::FromArgb(233, 150, 122);
        clearButton->ForeColor = Color::Black;
        clearButton->FlatStyle = FlatStyle::Flat;
        clearButton->Click += gcnew EventHandler(this, &MainForm::ClearButton_Click);
        resultsGroupBox->Controls->Add(clearButton);
    }

protected:
    void BoostedTreesButton_Click(Object^ sender, EventArgs^ e) {
        // Hide combined results panel and show single result
        combinedResultsPanel->Visible = false;
        satisfactionLabel->Visible = true;
        satisfactionOutput->Visible = true;

        // Calculate using Boosted Trees
        try {
            array<double>^ inputs = ValidateAndGetInputs();
            if (inputs != nullptr) {
                pin_ptr<double> inputsPtr = &inputs[0];
                double btResult = DeploymentCase_BoostedTrees(inputsPtr);
                int btLevel = static_cast<int>(btResult);
                satisfactionOutput->Text = GetSatisfactionLevelForBoostedAndRandom(btLevel);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при расчете результатов: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void RandomForestButton_Click(Object^ sender, EventArgs^ e) {
        // Hide combined results panel and show single result
        combinedResultsPanel->Visible = false;
        satisfactionLabel->Visible = true;
        satisfactionOutput->Visible = true;

        // Calculate using Random Forest
        try {
            array<double>^ inputs = ValidateAndGetInputs();
            if (inputs != nullptr) {
                pin_ptr<double> inputsPtr = &inputs[0];
                double rfResult = DeploymentCase_RandomForest(inputsPtr);
                int rfLevel = static_cast<int>(rfResult);
                satisfactionOutput->Text = GetSatisfactionLevelForBoostedAndRandom(rfLevel);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при расчете результатов: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void ANNButton_Click(Object^ sender, EventArgs^ e) {
        // Hide combined results panel and show single result
        combinedResultsPanel->Visible = false;
        satisfactionLabel->Visible = true;
        satisfactionOutput->Visible = true;

        // Calculate using Neural Network
        try {
            array<double>^ inputs = ValidateAndGetInputs();
            if (inputs != nullptr) {
                pin_ptr<double> inputsPtr = &inputs[0];
                double nnResult = DeploymentCase_NeuralNetwork(inputsPtr);
                int nnLevel = static_cast<int>(nnResult);
                satisfactionOutput->Text = GetSatisfactionLevelForANN(nnLevel);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при расчете результатов: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void AllMethodsButton_Click(Object^ sender, EventArgs^ e) {
        // Show combined results panel and hide single result
        combinedResultsPanel->Visible = true;
        satisfactionLabel->Visible = false;
        satisfactionOutput->Visible = false;

        // Calculate using all methods
        try {
            array<double>^ inputs = ValidateAndGetInputs();
            if (inputs != nullptr) {
                pin_ptr<double> inputsPtr = &inputs[0];

                // Boosted Trees
                double btResult = DeploymentCase_BoostedTrees(inputsPtr);
                int btLevel = static_cast<int>(btResult);
                satisfactionOutputs[0]->Text = GetSatisfactionLevelForBoostedAndRandom(btLevel);

                // Random Forest
                double rfResult = DeploymentCase_RandomForest(inputsPtr);
                int rfLevel = static_cast<int>(rfResult);
                satisfactionOutputs[1]->Text = GetSatisfactionLevelForBoostedAndRandom(rfLevel);

                // Neural Network
                double nnResult = DeploymentCase_NeuralNetwork(inputsPtr);
                int nnLevel = static_cast<int>(nnResult);
                satisfactionOutputs[2]->Text = GetSatisfactionLevelForANN(nnLevel);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при расчете результатов: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    void ClearButton_Click(Object^ sender, EventArgs^ e) {
        try {

            for (int i = 0; i < factorInputs->Length; i++) {
                factorInputs[i]->Clear();
            }


            satisfactionOutput->Clear();


            if (satisfactionOutputs != nullptr) {
                for (int i = 0; i < satisfactionOutputs->Length; i++) {
                    satisfactionOutputs[i]->Clear();
                }
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show(L"Ошибка при очистке данных: " + ex->Message,
                L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    array<double>^ ValidateAndGetInputs() {
        array<double>^ inputs = gcnew array<double>(20);

        for (int i = 0; i < 20; i++) {
            if (String::IsNullOrWhiteSpace(factorInputs[i]->Text)) {
                MessageBox::Show(String::Format(L"Пожалуйста, введите значение для фактора \"{0}\"", factorNames[i]),
                    L"Ошибка ввода", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return nullptr;
            }

            if (!Double::TryParse(factorInputs[i]->Text, inputs[i]) || inputs[i] < 0 || inputs[i] > 10) {
                MessageBox::Show(String::Format(L"Значение для фактора \"{0}\" должно быть числом от 0 до 10", factorNames[i]),
                    L"Ошибка ввода", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return nullptr;
            }
        }

        return inputs;
    }

    String^ GetSatisfactionLevelForBoostedAndRandom(int level) {
        switch (level) {
        case 1: return L"Низкий";
        case 2: return L"Средний";
        case 3: return L"Высокий";
        default: return L"Неопределен";
        }
    }

    String^ GetSatisfactionLevelForANN(int level) {
        switch (level) {
        case 1: return L"Высокий";
        case 2: return L"Низкий";
        case 3: return L"Средний";
        default: return L"Неопределен";
        }
    }
};

[STAThread]
int main(array<String^>^ args) {
    try {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Application::Run(gcnew MainForm());
        return 0;
    }
    catch (Exception^ ex) {
        MessageBox::Show(L"Критическая ошибка: " + ex->Message,
            L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return 1;
    }
}

#pragma managed(pop)
#endif
