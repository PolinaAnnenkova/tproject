<template>
  <div>
    <div class="flex bg-blue-100">
      <main class="flex-1 p-4">
        <div v-if="currentTab === 'transactions'">
          <h2 class="text-2xl mb-4">Список проводок</h2>
          <div class="mb-4">
            <label class="inline-flex items-center">
              <input type="radio" class="form-radio" v-model="timeFilter" value="all" />
              <span class="ml-2">За все время</span>
            </label>
            <label class="inline-flex items-center ml-6">
              <input type="radio" class="form-radio" v-model="timeFilter" value="day" />
              <span class="ml-2">За день недели</span>
            </label>
            <label class="inline-flex items-center ml-6">
              <input type="radio" class="form-radio" v-model="timeFilter" value="month" />
              <span class="ml-2">За месяц</span>
            </label>
          </div>
          <div v-if="timeFilter === 'day'" class="mb-4">
            <input type="date" v-model="selectedDate" class="form-input px-4 py-2 rounded" />
          </div>
          <table class="min-w-full bg-white">
            <thead class="bg-blue-300">
              <tr>
                <th class="w-1/6 px-4 py-2">Дата</th>
                <th class="w-1/6 px-4 py-2">Количество часов</th>
                <th class="w-1/3 px-4 py-2">Описание</th>
                <th class="w-1/6 px-4 py-2">Задача</th>
                <th class="w-1/6 px-4 py-2 text-center">Действия</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="(transaction, index) in filteredTransactions" :key="index" :class="transactionClass(transaction.date)">
                <td class="px-4 py-2">
                  <input type="date" v-if="editingDate === transaction.date" v-model="editTransactionData.date" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ transaction.date }}</span>
                </td>
                <td class="px-4 py-2">
                  <input v-if="editingDate === transaction.date" v-model="editTransactionData.hours" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ transaction.hours }}</span>
                </td>
                <td class="px-4 py-2">
                  <input v-if="editingDate === transaction.date" v-model="editTransactionData.description" class="w-full px-2 py-1 border rounded" />
                  <span v-else>{{ transaction.description }}</span>
                </td>
                <td class="px-4 py-2">
                  <div v-if="editingDate === transaction.date">
                    <select v-model="editTransactionData.task" class="w-full px-2 py-1 border rounded" @change="handleTaskChange">
                      <option v-for="task in tasks" :key="task.name" :value="task.name">{{ task.name }}</option>
                      <option value="new">Добавить новую задачу</option>
                    </select>
                    <input v-if="isEditingNewTask" v-model="newTaskName" class="w-full px-2 py-1 border rounded mt-2" placeholder="Введите название новой задачи" />
                  </div>
                  <span v-else>{{ transaction.task }}</span>
                </td>
                <td class="px-4 py-2 text-center">
                  <button @click="editTransaction(transaction)" class="text-blue-500 mr-2" v-if="editingDate !== transaction.date">✏️</button>
                  <button @click="saveTransaction(transaction.date)" class="text-green-500 mr-2" v-if="editingDate === transaction.date">💾</button>
                  <button @click="cancelEdit()" class="text-red-500 mr-2" v-if="editingDate === transaction.date">✖️</button>
                  <button @click="deleteTransaction(transaction.date)" class="text-red-500">🗑️</button>
                </td>
              </tr>
              <tr :class="transactionClass(newTransaction.date)">
                <td class="px-4 py-2">
                  <input type="date" v-model="newTransaction.date" class="w-full px-2 py-1 border rounded" placeholder="Дата" />
                </td>
                <td class="px-4 py-2">
                  <input v-model="newTransaction.hours" class="w-full px-2 py-1 border rounded" placeholder="Количество часов" />
                </td>
                <td class="px-4 py-2">
                  <input v-model="newTransaction.description" class="w-full px-2 py-1 border rounded" placeholder="Описание" />
                </td>
                <td class="px-4 py-2">
                  <div>
                    <select v-model="newTransaction.task" class="w-full px-2 py-1 border rounded" @change="handleNewTaskChange">
                      <option v-for="task in tasks" :key="task.name" :value="task.name">{{ task.name }}</option>
                      <option value="new">Добавить новую задачу</option>
                    </select>
                    <input v-if="isAddingNewTask" v-model="newTaskName" class="w-full px-2 py-1 border rounded mt-2" placeholder="Введите название новой задачи" />
                  </div>
                </td>
                <td class="px-4 py-2 text-center">
                  <button @click="addTransaction()" class="text-blue-500">➕</button>
                </td>
              </tr>
            </tbody>
          </table>
          <div v-if="errorMessage" class="mt-4 text-red-500">
            {{ errorMessage }}
          </div>
        </div>
      </main>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    nowIndex: {
      type: Number,
      default: 0
    },
    transactions: {
      type: Array
    },
    tasks: {
      type: Array,
      required: true
    },
    addTask: {
      type: Function,
      required: true
    }
  },
  data() {
    return {
      currentTab: 'transactions',
      timeFilter: 'all',
      selectedDate: null,
      newTransaction: { date: '', hours: '', description: '', task: '' },
      editingDate: null,
      editTransactionData: { date: '', hours: '', description: '', task: '' },
      errorMessage: '',
      newTaskName: '',
      isAddingNewTask: false,
      isEditingNewTask: false
    };
  },
  computed: {
    filteredTransactions() {
      if (this.timeFilter === 'day' && this.selectedDate) {
        return this.transactions[this.nowIndex].filter(transaction => transaction.date === this.selectedDate);
      }
      if (this.timeFilter === 'month') {
        const currentMonth = new Date().getMonth();
        const currentYear = new Date().getFullYear();
        return this.transactions[this.nowIndex].filter(transaction => {
          const transactionDate = new Date(transaction.date);
          return transactionDate.getMonth() === currentMonth && transactionDate.getFullYear() === currentYear;
        });
      }
      return this.transactions[this.nowIndex];
    },
    transactionsGroupedByDate() {
      return this.transactions[this.nowIndex].reduce((acc, transaction) => {
        if (!acc[transaction.date]) {
          acc[transaction.date] = [];
        }
        acc[transaction.date].push(transaction);
        return acc;
      }, {});
    }
  },
  methods: {
    validateTransactionData(transaction, isNewTransaction = false) {
      const currentDate = new Date().toISOString().split('T')[0];
      if (!transaction.date || !transaction.hours || !transaction.description || (!transaction.task && !this.newTaskName)) {
        this.errorMessage = 'Все поля должны быть заполнены.';
        return false;
      }
      if (new Date(transaction.date) > new Date(currentDate)) {
        this.errorMessage = 'Дата не может быть в будущем.';
        return false;
      }
      if (isNaN(transaction.hours) || transaction.hours < 0 || transaction.hours > 24) {
        this.errorMessage = 'Количество часов должно быть числом от 0 до 24.';
        return false;
      }

      // Проверка, что общая сумма часов за день не превышает 24
      const transactionsForDate = this.transactionsGroupedByDate[transaction.date] || [];
      const totalHours = transactionsForDate.reduce((total, t) => total + (t.date === transaction.date && t !== transaction ? Number(t.hours) : 0), 0);
      const newTotalHours = totalHours + Number(transaction.hours);
      if (newTotalHours > 24) {
        this.errorMessage = 'Общая сумма часов за день не может превышать 24 часа.';
        return false;
      }

      this.errorMessage = '';
      return true;
    },
    addTransaction() {
      if (this.isAddingNewTask && this.newTaskName) {
        this.addTask(this.newTaskName);
        this.newTransaction.task = this.newTaskName;
      }
      if (this.validateTransactionData(this.newTransaction, true)) {
        this.transactions[this.nowIndex].push({ ...this.newTransaction });
        this.newTransaction = { date: '', hours: '', description: '', task: '' };
        this.newTaskName = '';
        this.isAddingNewTask = false;
      }
    },
    editTransaction(transaction) {
      this.editingDate = transaction.date;
      this.editTransactionData = { ...transaction };
    },
    saveTransaction(date) {
      if (this.isEditingNewTask && this.newTaskName) {
        this.addTask(this.newTaskName);
        this.editTransactionData.task = this.newTaskName;
      }
      if (this.validateTransactionData(this.editTransactionData)) {
        const index = this.transactions[this.nowIndex].findIndex(transaction => transaction.date === date);
        if (index !== -1) {
          this.transactions[this.nowIndex][index] = { ...this.editTransactionData };
          this.editingDate = null;
          this.editTransactionData = { date: '', hours: '', description: '', task: '' };
          this.isEditingNewTask = false;
          this.newTaskName = '';
        }
      }
    },
    cancelEdit() {
      this.editingDate = null;
      this.editTransactionData = { date: '', hours: '', description: '', task: '' };
      this.errorMessage = '';
    },
    deleteTransaction(date) {
      const index = this.transactions[this.nowIndex].findIndex(transaction => transaction.date === date);
      if (index !== -1) {
        this.transactions[this.nowIndex].splice(index, 1);
      }
    },
    handleNewTaskChange() {
      if (this.newTransaction.task === 'new') {
        this.isAddingNewTask = true;
      } else {
        this.isAddingNewTask = false;
      }
    },
    handleTaskChange() {
      if (this.editTransactionData.task === 'new') {
        this.isEditingNewTask = true;
      } else {
        this.isEditingNewTask = false;
      }
    },
    transactionClass(date) {
      const transactionsForDate = this.transactionsGroupedByDate[date] || [];
      const totalHours = transactionsForDate.reduce((total, transaction) => total + Number(transaction.hours), 0);

      if (totalHours < 8) {
        return 'bg-yellow-200';
      } else if (totalHours === 8) {
        return 'bg-green-200';
      } else if (totalHours > 8) {
        return 'bg-red-200';
      } else {
        return 'bg-gray-200';
      }
    }
  }
};
</script>

<style scoped>
/* Add your styles here */
</style>
