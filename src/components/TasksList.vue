<template>
    <div>

        <div class="flex bg-blue-100">

            <main class="flex-1 p-4">

                <div v-if="currentTab === 'tasks'">
                    <h2 class="text-2xl mb-4">Список задач</h2>
                    <button @click="currentTab = 'addTask'"
                            :class="{'text-blue-500': currentTab === 'addTask', 'bg-blue-300 text-white': currentTab !== 'addTask'}"
                            class="px-4 py-2 rounded mb-2">
                        Добавить задачу
                    </button>

                    <table class="min-w-full bg-white">
                        <thead class="bg-blue-300">
                            <tr>
                                <th class="text-white w-1/3 px-4 py-2">Название задачи</th>
                                <th class="text-white w-1/6 px-4 py-2">Проект</th>
                                <th class="text-white w-1/6 px-4 py-2">Активный</th>
                                <th class="text-white w-1/6 px-4 py-2">Проводки</th>
                                <th class="text-white w-1/3 px-4 py-2 text-center">Действия</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="(task, index) in tasks" :key="task.name" class="border-t">
                                <td class="text-center px-4 py-2">{{ task.name }}</td>
                                <td class="text-center px-4 py-2">{{ task.name_project }}</td>
                                <td class="text-center px-4 py-2">{{ task.active ? 'Да' : 'Нет' }}</td>
                                <td class="text-center px-4 py-2">
    <li v-for="t in task.time">{{ t.date }} {{t.hour  }}</li> </td>
    <td class="px-4 py-2 text-center">
        <button @click="editTask(index);currentTab = 'editTask';" class="text-blue-500 mr-2">✏️</button>
        <button @click="deleteTask(index)" class="text-red-500 mr-2">🗑️</button>

    </td>
    </tr>

    </tbody>
    </table>
    </div>
    <div v-if="currentTab === 'addTask'">
        <h2 class="text-2xl mb-4">Добавление задачи</h2>
        <ul>
            <label for="name">Название задачи:    </label>
            <input type="text"
                   v-model="newTask.name"
                   class=" px-3 py-1 mt-2 border border-gray-300 rounded-lg"
                   required />
        </ul>
        <ul>
            <label for="name">Название проекта:    </label>
            <input type="text"
                   v-model="newTask.name_project"
                   class=" px-3 py-1 mt-2 border border-gray-300 rounded-lg"
                   required />
        </ul>
        <ul>
            <label for="name">Активен:    </label>
            <input type="checkbox" v-model="newTask.active" class="mt-4" />
        </ul>
        <nav class="flex space-x-4 mb-4">
            <button @click="addTask();currentTab = 'tasks';"
                    :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
                    class="px-4 py-2 rounded mb-2 mt-4 space-x-4">
                Сохранить
            </button>
            <button @click="currentTab = 'tasks'"
                    :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
                    class="px-7 py-2 rounded mb-2 mt-4 ">
                Отмена
            </button>
        </nav>
    </div>
    <div v-if="currentTab === 'editTask'">
        <h2 class="text-2xl mb-4">Редактирование задачи</h2>
        <ul>
            <label for="name">Название задачи:    </label>
            <input type="text"
                   v-model="newTask.name"
                   class=" px-3 py-1 mt-2 border border-gray-300 rounded-lg" placeholder=""
                   required />
        </ul>
        <ul>
            <label for="name">Название проекта:    </label>
            <input type="text"
                   v-model="newTask.name_project"
                   class=" px-3 py-1 mt-2 border border-gray-300 rounded-lg"
                   required />
        </ul>
        <ul>
            <label for="name">Активен:    </label>
            <input type="checkbox" v-model="newTask.active" class="mt-4" />
        </ul>
        <nav class="flex space-x-4 mb-4">
            <button @click="addTask();currentTab = 'tasks';"
                    :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
                    class="px-4 py-2 rounded mb-2 mt-4 space-x-4">
                Сохранить
            </button>
            <button @click="currentTab = 'tasks'"
                    :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
                    class="px-7 py-2 rounded mb-2 mt-4 ">
                Отмена
            </button>
        </nav>
    </div>
    </main>
    </div>
    </div>
</template>

<script>
  export default {
    data() {
      return {
          ed: {
             type: Number,
             default: 0
    },
          currentTab: 'tasks',


        tasks: [
            { name: 'Название1', name_project: 'Проект1', active: true, time: [{ date: '01.01.2024', hour: '02:30' }, { date: '02.01.2024', hour: '08:30' }] },
            { name: 'Название2', name_project: 'Проект1', active: true, time: [] },
            { name: 'Название3', name_project: 'Проект2', active: true, time: [{ date: '05.05.2024', hour: '02:14' }] },
            { name: 'Название4', name_project: 'Проект3', active: false, time: [{ date: '06.06.2024', hour: '06:45' }, { date: '07.06.2024', hour: '03:25' }]},
            { name: 'Название5', name_project: 'Проект3', active: true, time: [{ date: '08.06.2024', hour: '01:10' }]},
        ],
          newTask: { name: '', name_project: '', active: false, time: []}
      };
    },
    methods: {

        addTask() {
            if (this.newTask.name && this.newTask.name_project) {
          this.tasks.push({ ...this.newTask });
                this.newTask = { name: '', name_project: '', active: false, time: [] };
                
        }
      },
        editTask(index) {
            this.newTask = { ...this.tasks[index] };
            this.tasks.splice(index, 1);
      },
        deleteTask(index) {
            this.tasks.splice(index, 1);
      },
        saveTask(index) {
            this.tasks.splice(index, 1, this.newTask);
            this.newProject = { name: '', name_project: '', active: false, time: [] };
      }
    }
  };
</script>

<style scoped>
    /* Add any additional styles here */
</style>
